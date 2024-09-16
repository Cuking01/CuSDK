#pragma once

struct WAV_Header
{
    // RIFF Header
    char riff_header[4] = {'R', 'I', 'F', 'F'}; // Contains "RIFF"
    int wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
    char wave_header[4] = {'W', 'A', 'V', 'E'}; // Contains "WAVE"

    // Format Header
    char fmt_header[4] = {'f', 'm', 't', ' '}; // Contains "fmt " (includes trailing space)
    int fmt_chunk_size;                        // Should be 16 for PCM
    short audio_format;                        // Should be 1 for PCM. 3 for IEEE Float
    short num_channels;
    int sample_rate;
    int byte_rate;          // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
    short sample_alignment; // num_channels * Bytes Per Sample
    short bit_depth;        // Number of bits per sample

    // Data
    char data_header[4] = {'d', 'a', 't', 'a'}; // Contains "data"
    int data_bytes; // Number of bytes in data. Number of samples * num_channels * sample byte size

    void write(std::vector<uint8_t>&buf,const uint8_t* data, size_t dataLength)
    {
    	buf.resize(44+data_bytes);
    	memcpy(buf.data(),this,44);
    	memcpy(buf.data()+44,data,data_bytes);
    }
};


template<typename Sample_T>
PCM<Sample_T> wav_decode_from_file(std::string path)
{
	PCM pcm;
	wav_header h;

    FP fp(path,"rb");
	fread(&h,44,1,fp);

    

	std::vector<uint8_t> buf(h.data_bytes);
	buf.resize(fread(buf.data(),1,h.data_bytes,fp));

	memcpy(&h,buf.data(),44);
	pcm.channel_num=h.num_channels;
	pcm.sample_rate=h.sample_rate;
	pcm.sample_num=h.data_bytes/h.sample_alignment;

	printf("%u %u %u\n",pcm.channel_num,pcm.sample_rate,pcm.sample_num);
	pcm.data.resize(pcm.sample_num*pcm.channel_num);

	for(int i=0;i<pcm.sample_num*pcm.channel_num;i++)
	{
		pcm.data[i]=i[(float*)(buf.data()+44)]*32767;
	}

	return pcm;
}

void encode_to_file(const PCM& pcm, std::string path)
{
    auto bufferSize = sizeof(wav_header) + pcm.data.size() * 2;
    std::vector<uint8_t> buffer;
    buffer.reserve(bufferSize);

    encode(pcm, buffer);

    wav_header h;
    h.wav_size = 36 + pcm.sample_num * pcm.channel_num * sizeof(int16_t);
    h.fmt_chunk_size = 16;
    h.audio_format = 1;
    h.num_channels = pcm.channel_num;
    h.sample_rate = pcm.sample_rate;
    h.byte_rate = pcm.sample_rate * pcm.channel_num * 2;
    h.sample_alignment = pcm.channel_num * 2;
    h.bit_depth = 16;
	h.data_bytes = pcm.sample_num * pcm.channel_num * 2;

	h.write(buf, (uint8_t*) pcm.data.data(), pcm.data.size() * 2);
    
    FILE*fp=fopen(path.c_str(),"wb");
    fwrite(buffer.data(),1,buffer.size(),fp);
    fclose(fp);
}

