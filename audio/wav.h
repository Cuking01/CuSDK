#pragma once

constexpr u3 wav_format_integer=1;
constexpr u3 wav_format_float=3;


struct WAV_Header
{
    // RIFF Header
    char riff_header[4] = {'R', 'I', 'F', 'F'}; // Contains "RIFF"
    u2 wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
    char wave_header[4] = {'W', 'A', 'V', 'E'}; // Contains "WAVE"

    // Format Header
    char fmt_header[4] = {'f', 'm', 't', ' '}; // Contains "fmt " (includes trailing space)
    u2 fmt_chunk_size=16;                        // Should be 16 for PCM
    u1 audio_format;                        // Should be 1 for PCM. 3 for IEEE Float
    u1 num_channels;
    u2 sample_rate;
    u2 byte_rate;          // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
    u1 sample_alignment; // num_channels * Bytes Per Sample
    u1 bit_depth;        // Number of bits per sample

    // Data
    char data_header[4] = {'d', 'a', 't', 'a'}; // Contains "data"
    u2 data_bytes; // Number of bytes in data. Number of samples * num_channels * sample byte size

    void load(File&fp)
    {
        u3 read_size=fread(this,44,1,fp);

        auto err_desc=std::format("wav file [{}] data is damaged.",fp.name());

        cu_assert(read_size==44,err_desc);
        cu_assert(wav_size>data_bytes&&wav_size==data_bytes+36,err_desc);
        cu_assert(fmt_chunk_size==16,err_desc);
        cu_assert(num_channels>0,err_desc);
        cu_assert(sample_rate>0,err_desc);
        cu_assert(bit_depth%8==0,err_desc);

        u3 byte_per_sample=bit_depth/8;

        bool integer_restrict=audio_format==wav_format_integer&&is(bit_depth).one_of(8,16,32);
        bool float_restrict=audio_format==wav_format_float&&is(bit_depth).one_of(32,64);

        cu_assert(integer_restrict||float_restrict,err_desc);

        //防溢出
        cu_assert(byte_rate>=std::max(byte_per_sample,sample_rate,num_channels),err_desc);
        cu_assert(sample_alignment>=std::max(num_channels,byte_per_sample),err_desc);

        //数值约束
        cu_assert(byte_rate==byte_per_sample*sample_rate*num_channels,err_desc);
        cu_assert(sample_alignment==num_channels*byte_per_sample,err_desc);

    }

};


template<Sample_Type T>
PCM<T> wav_decode_from_file(std::string path)
{
	PCM<T> pcm;
	wav_header h;
    File file(path,"rb");
	h.load(file);
    
    std::vector<byte> buf(h.data_bytes);
    cu_assert(fread(buf.data(),1,h.data_bytes,file)==data_bytes,err_desc);

    pcm.channel_num=h.num_channels;
    pcm.sample_rate=h.sample_rate;
    pcm.sample_num=h.data_bytes/h.sample_alignment;
    pcm.data.resize(pcm.sample_num*pcm.channel_num);

    //采样数乘声道数
    u3 n=pcm.sample_num*pcm.channel_num;

    if(h.audio_format==wav_format_integer)
    {
        if(h.bit_depth==8)
            sample_trans_n(pcm.data.data(),(s0*)buf.data(),n);
        else if(h.bit_depth==16)
            sample_trans_n(pcm.data.data(),(s1*)buf.data(),n);
        else
            sample_trans_n(pcm.data.data(),(s2*)buf.data(),n);
    }
    else if(h.audio_format==wav_format_float)
    {
        if(h.bit==32)
            sample_trans_n(pcm.data.data(),(f2*)buf.data(),n);
        else
            sample_trans_n(pcm.data.data(),(f3*)buf.data(),n);
    }

	return pcm;
}

template<Sample_Type T>
void wav_encode_to_file(const PCM<T>& pcm, std::string path)
{
    WAV_Header h;

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

