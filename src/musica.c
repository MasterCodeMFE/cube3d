/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musica.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:02:48 by manufern          #+#    #+#             */
/*   Updated: 2025/04/25 13:29:35 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <alsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

// Assumed definitions - make sure these are defined in your actual code
// #define SAMPLE_RATE 44100
// #define AMPLITUDE 0.5 // Maximum amplitude (0.0 to 1.0)
// #define NOTE_DURATION 0.5 // Duration of each note in seconds

// ADSR Envelope Parameters (in seconds)
#define ATTACK_TIME 0.01
#define DECAY_TIME 0.05
#define SUSTAIN_LEVEL 0.7 // Sustain level (0.0 to 1.0)
// Release time is handled by the duration of the note buffer vs how long it's played
// For simplicity here, let's assume the total length passed to generate_wave is the
// full duration including A, D, S, and R phases. The R phase starts when the
// sustain phase ends within the allocated buffer time.

// Harmonic Structure for richer waveform
// Coefficients for fundamental and harmonics (e.g., for a sawtooth-like sound)
// You can experiment with these values
#define NUM_HARMONICS 5
float harmonic_coeffs[NUM_HARMONICS] = {1.0f, 0.5f, 0.33f, 0.25f, 0.1f}; // Amplitudes for 1st, 2nd, 3rd... harmonics

int notes[] = {130, 146, 164, 196, 220, 261, 293, 329, 392, 440, 523}; // Frequencies

void generate_wave(short *buffer, int freq, int length) {
    // Calculate ADSR sample counts
    int attack_samples = ATTACK_TIME * SAMPLE_RATE;
    int decay_samples = DECAY_TIME * SAMPLE_RATE;
    // The sustain phase lasts until the release phase starts.
    // Let's define a Release Time constant and calculate sustain samples.
    // Total length is A + D + S + R samples.
    // R_TIME is assumed to be part of the total length passed to generate_wave.
    // Let's use a RELASE_TIME constant for the *conceptual* release phase duration.
    // The actual release phase will be the end of the buffer.
    #define RELEASE_TIME 0.1 // Conceptual release time in seconds
    int release_samples_conceptual = RELEASE_TIME * SAMPLE_RATE;

    // Ensure attack and decay phases fit within the length
    if (attack_samples + decay_samples >= length) {
        attack_samples = length / 2;
        decay_samples = length - attack_samples;
        if (decay_samples < 0) decay_samples = 0;
    }
     if (attack_samples + decay_samples + release_samples_conceptual >= length) {
        // Adjust release if it's too long
        release_samples_conceptual = length - attack_samples - decay_samples;
         if (release_samples_conceptual < 0) release_samples_conceptual = 0;
    }


    int sustain_samples_start = attack_samples + decay_samples;
    int release_samples_start = length - release_samples_conceptual;
     if (release_samples_start < sustain_samples_start) release_samples_start = sustain_samples_start;


    for (int i = 0; i < length; i++) {
        float envelope = 0.0f;
        float t = (float)i / SAMPLE_RATE; // Time in seconds for the current sample

        // ADSR Envelope Calculation
        if (i < attack_samples) {
            // Attack Phase: Linear rise from 0 to 1.0
            envelope = (float)i / attack_samples;
        } else if (i < sustain_samples_start) {
            // Decay Phase: Linear fall from 1.0 to SUSTAIN_LEVEL
            envelope = 1.0f - ((float)(i - attack_samples) / decay_samples) * (1.0f - SUSTAIN_LEVEL);
        } else if (i < release_samples_start) {
            // Sustain Phase: Hold at SUSTAIN_LEVEL
            envelope = SUSTAIN_LEVEL;
        } else {
            // Release Phase: Linear fall from SUSTAIN_LEVEL to 0
             if (length - release_samples_start > 0) {
                 envelope = SUSTAIN_LEVEL * (float)(length - i) / (length - release_samples_start);
             } else {
                 envelope = 0.0f; // Avoid division by zero if release_samples_start is the end
             }

        }

        // Ensure envelope is not negative due to float inaccuracies
        if (envelope < 0.0f) envelope = 0.0f;
        if (envelope > 1.0f) envelope = 1.0f; // Should not happen with this logic, but good practice

        // Waveform Generation with Harmonics
        float sample_value = 0.0f;
        for (int h = 0; h < NUM_HARMONICS; h++) {
            // Add harmonic with decreasing amplitude
            sample_value += harmonic_coeffs[h] * sin(2.0f * M_PI * freq * (h + 1) * t);
        }

        // Apply Envelope and Amplitude
        float final_sample = AMPLITUDE * envelope * sample_value;

        // Convert to 16-bit signed short
        // Clamp to avoid clipping, although AMPLITUDE and envelope should prevent this
        long scaled_sample = (long)(final_sample * 32767.0f);
        if (scaled_sample > 32767) scaled_sample = 32767;
        if (scaled_sample < -32768) scaled_sample = -32768;

        buffer[i] = (short)scaled_sample;
    }
}

// The play_music function remains largely the same, but it will now play notes
// generated with the improved generate_wave function.
void *play_music(void *arg) {
    (void)arg;

    snd_pcm_t *handle;
    int err;

    // Open PCM device
    if ((err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        fprintf(stderr, "Error opening PCM device: %s\n", snd_strerror(err));
        return NULL;
    }

    // Allocate and set hardware parameters
    snd_pcm_hw_params_t *params;
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(handle, params);

    // Configure hardware parameters
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(handle, params, 1); // Mono

    unsigned int sample_rate = SAMPLE_RATE;
    snd_pcm_hw_params_set_rate_near(handle, params, &sample_rate, 0);

    // Configure buffer and period sizes
    snd_pcm_uframes_t buffer_size = SAMPLE_RATE; // 1 second buffer
    snd_pcm_uframes_t period_size = SAMPLE_RATE / 4; // 0.25 second period
    snd_pcm_hw_params_set_buffer_size_near(handle, params, &buffer_size);
    snd_pcm_hw_params_set_period_size_near(handle, params, &period_size, 0);

    // Apply hardware parameters
    if ((err = snd_pcm_hw_params(handle, params)) < 0) {
        fprintf(stderr, "Unable to set HW params: %s\n", snd_strerror(err));
        snd_pcm_close(handle);
        return NULL;
    }

    // Allocate and set software parameters
    snd_pcm_sw_params_t *swparams;
    snd_pcm_sw_params_alloca(&swparams);
    snd_pcm_sw_params_current(handle, swparams);
    snd_pcm_sw_params_set_start_threshold(handle, swparams, period_size);
    snd_pcm_sw_params_set_avail_min(handle, swparams, period_size);
    snd_pcm_sw_params(handle, swparams);

    // Prepare the PCM device
    snd_pcm_prepare(handle);

    // Calculate buffer size for a single note
    int note_buffer_size = NOTE_DURATION * SAMPLE_RATE;
    short *note_buffer = malloc(note_buffer_size * sizeof(short));
    if (!note_buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        snd_pcm_close(handle);
        return NULL;
    }

    srand(time(NULL)); // Seed random number generator

    // Main playback loop
    while (1) {
        // Select a random note frequency
        int note_index = rand() % (sizeof(notes)/sizeof(notes[0]));
        int current_freq = notes[note_index];

        // Generate the waveform with improved sound (ADSR and Harmonics)
        generate_wave(note_buffer, current_freq, note_buffer_size);

        // Write the generated audio data to the PCM device
        int frames_written = snd_pcm_writei(handle, note_buffer, note_buffer_size);

        // Handle potential ALSA errors (underrun, suspended)
        if (frames_written == -EPIPE) {
            // Underrun occurred - buffer was not filled in time
            fprintf(stderr, "Underrun occurred\n");
            snd_pcm_prepare(handle); // Try to recover by preparing the device
        } else if (frames_written < 0) {
            // Other write error
            fprintf(stderr, "Write error: %s\n", snd_strerror(frames_written));
            // Attempt recovery
            snd_pcm_recover(handle, frames_written, 0);
        } else if (frames_written != note_buffer_size) {
            // Not all frames were written, this shouldn't typically happen with blocking write
            fprintf(stderr, "Short write, expected %d frames, wrote %d\n", note_buffer_size, frames_written);
        }

        // Wait before playing the next note. The sleep duration affects the rhythm.
        // You might want to adjust this based on NOTE_DURATION and desired spacing.
        usleep(NOTE_DURATION * 1000000); // Sleep for the duration of the note
        // usleep(NOTE_DURATION * 500000); // Example: Sleep for half the note duration for faster sequence
    }

    // Cleanup (this part will not be reached in the infinite loop)
    free(note_buffer);
    snd_pcm_drain(handle); // Wait for any remaining samples to be played
    snd_pcm_close(handle);
    return NULL;
}