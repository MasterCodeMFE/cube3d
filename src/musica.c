/* ************************************************************************** */
/*                                                                            */
/*                        Improved music engine (ALSA)                       */
/*                                                                            */
/*   - Melodía simple en bucle con armónicos y ADSR                          */
/*   - Parámetros fáciles de ajustar                                          */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <alsa/asoundlib.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_HARMONICS 4
#define SAMPLE_RATE 44100
#define CHANNELS 1
#define FORMAT SND_PCM_FORMAT_S16_LE
#define AMPLITUDE_SCALE 0.85f

// Small helper: generate one note into a buffer with ADSR + harmonics
static void generate_note(short *buf, size_t frames, double freq, double duration_seconds)
{
	double t_step = 1.0 / (double)SAMPLE_RATE;
	double total = duration_seconds;
	size_t total_frames = (size_t)(total * SAMPLE_RATE);
	if (frames < total_frames) total_frames = frames;

	// ADSR in seconds (attack, decay, sustain level, release)
	double A = 0.01; // quick attack
	double D = 0.05;
	double S = 0.8;
	double R = 0.08;

	// harmonic amplitudes (fundamental strongest)
	double harm_amp[NUM_HARMONICS] = {1.0, 0.35, 0.18, 0.08};

	for (size_t i = 0; i < total_frames; ++i)
	{
		double t = (double)i * t_step;
		// envelope
		double env;
		if (t < A)
			env = (t / A);
		else if (t < A + D)
			env = 1.0 - (1.0 - S) * ((t - A) / D);
		else if (t < total - R)
			env = S;
		else
			env = S * (1.0 - ((t - (total - R)) / R));

		// waveform with harmonics (additive synthesis)
		double sample = 0.0;
		for (int h = 0; h < NUM_HARMONICS; ++h)
		{
			double mul = (double)(h + 1);
			sample += harm_amp[h] * sin(2.0 * M_PI * freq * mul * t);
		}
		// normalize and apply envelope & amplitude
		sample = (sample / 1.6) * env * AMPLITUDE_SCALE;

		long s_int = (long)(sample * 32767.0);
		if (s_int > 32767) s_int = 32767;
		if (s_int < -32768) s_int = -32768;
		buf[i] = (short)s_int;
	}

	// zero remainder if any
	for (size_t i = total_frames; i < frames; ++i)
		buf[i] = 0;
}

// Simple melody (frequencies in Hz) and durations (seconds)
static double melody_freqs[] = {
	440.0, 494.0, 523.25, 440.0, 392.0, 440.0, 523.25, 587.33
};
static double melody_durs[] = {
	0.35, 0.35, 0.45, 0.25, 0.35, 0.35, 0.45, 0.65
};
static int melody_len = sizeof(melody_freqs) / sizeof(double);

void *play_music(void *arg)
{
	(void)arg;
	snd_pcm_t *handle;
	int err;

	if ((err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
	{
		fprintf(stderr, "Error opening PCM device: %s\n", snd_strerror(err));
		return NULL;
	}

	// hw params
	snd_pcm_hw_params_t *hw;
	snd_pcm_hw_params_malloc(&hw);
	snd_pcm_hw_params_any(handle, hw);
	snd_pcm_hw_params_set_access(handle, hw, SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(handle, hw, FORMAT);
	snd_pcm_hw_params_set_rate(handle, hw, SAMPLE_RATE, 0);
	snd_pcm_hw_params_set_channels(handle, hw, CHANNELS);

	// choose buffer/period
	unsigned int period_time = 100000; // 100ms
	unsigned int buffer_time = 400000; // 400ms
	snd_pcm_hw_params_set_period_time_near(handle, hw, &period_time, 0);
	snd_pcm_hw_params_set_buffer_time_near(handle, hw, &buffer_time, 0);

	if ((err = snd_pcm_hw_params(handle, hw)) < 0)
	{
		fprintf(stderr, "Unable to set HW params: %s\n", snd_strerror(err));
		snd_pcm_hw_params_free(hw);
		snd_pcm_close(handle);
		return NULL;
	}
	snd_pcm_hw_params_free(hw);

	// Prepare software params (use defaults)
	snd_pcm_prepare(handle);

	// allocate a buffer for one second max
	size_t max_frames = SAMPLE_RATE; // 1 second buffer
	short *buffer = malloc(sizeof(short) * max_frames);
	if (!buffer)
	{
		snd_pcm_close(handle);
		return NULL;
	}

	// Loop melody indefinitely (thread detached by caller)
	while (1)
	{
		for (int n = 0; n < melody_len; ++n)
		{
			double freq = melody_freqs[n];
			double dur = melody_durs[n];
			size_t frames = (size_t)(dur * SAMPLE_RATE);
			if (frames > max_frames) frames = max_frames;

			generate_note(buffer, frames, freq, dur);

			// write frames (handle partial writes)
			size_t offset = 0;
			while (offset < frames)
			{
				snd_pcm_sframes_t written = snd_pcm_writei(handle, buffer + offset, frames - offset);
				if (written < 0)
				{
					written = snd_pcm_recover(handle, (int)written, 1);
					if (written < 0)
					{
						fprintf(stderr, "snd_pcm_writei failed: %s\n", snd_strerror((int)written));
						break;
					}
				}
				else
					offset += (size_t)written;
			}
			// short pause between notes
			snd_pcm_drain(handle);
		}
		// loop
	}
	// cleanup (unreachable in normal flow)
	free(buffer);
	snd_pcm_close(handle);
	return NULL;
}