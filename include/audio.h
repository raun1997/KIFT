/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 16:59:39 by scollet           #+#    #+#             */
/*   Updated: 2017/10/06 16:59:40 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file audio.h
 * @brief Contains AudioData structure, and relevent audio functions.
 */

#include <stdint.h>
#include <string.h>

/**
 * Holds all of the necessary information for building an
 * audio file.
 * @var duration Contains how long the audio file will be in seconds.
 * @var formatType Contains the audio formatting type.
 * @var numberOfChannels Contains the number of audio channels.
 * @var sampleRate Contains the sample rate in Hertz.
 * @var frameIndex Contains the current frame to be processed.
 * @var maxFrameIndex Contains the number of frames that the audio file will store.
 * @var recordedSamples Contains the raw PCM audio data.
 */

typedef struct
{
    uint32_t duration;
    uint16_t formatType;
    uint16_t numberOfChannels;
    uint32_t sampleRate;
    uint32_t frameIndex;
    uint32_t maxFrameIndex;
    float* recordedSamples;
} AudioData;

void write_wav(char * filename, unsigned long num_samples, int16 *data, int s_rate);
    /* open a file named filename, write signed 16-bit values as a
        monoaural WAV file at the specified sampling rate
        and close the file
    */
int recordFLAC(AudioData data);
AudioData initAudioData(uint32_t sample_rate, uint16_t channels, uint32_t duration);
