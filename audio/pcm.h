#pragma once

template<Sample_Type T>
struct Sound_Track
{
	u3 sample_rate;
	std::vector<T> data;

	T& operator[](u3 i){return data[i];}
	T operator[](u3 i) const{return data[i];}

	u3 sample_num() const noexcept
    {
    	return data.size();
    }
};

using Sound_Track_i0=Sound_Track<s0>;
using Sound_Track_i1=Sound_Track<s1>;
using Sound_Track_i2=Sound_Track<s2>;
using Sound_Track_f2=Sound_Track<f2>;
using Sound_Track_f3=Sound_Track<f3>;

using Sound_Track_i=Sound_Track_i1;
using Sound_Track_f=Sound_Track_f2;

template<Sample_Type T>
struct PCM
{
    u3 sample_rate;
    u3 channel_num;
    std::vector<T> data;

    PCM(u3 sample_rate,u3 channel_num,u3 sample_num,const T*sample_data=0):
    	sample_rate(sample_rate),
    	channel_num(channel_num),
    	data(mul_s(channel_num,sample_num))
    {
    	if(sample_data)
    		memcpy(data.data(),sample_data,data.size()*sizeof(T));
    }

    PCM(const std::vector<Sound_Track<T>>&tracks)
    {
    	cu_assert(tracks.size());
    	sample_rate=tracks[0].sample_rate;
    	channel_num=tracks.size();

    	u3 sample_num=tracks[0].sample_num();
    	for(const auto& track:tracks)
    		cu_assert(track.sample_num()==sample_num);

    	data.resize(mul_s(sample_num,channel_num));
    	

    	for(u3 i=0;i<sample_num;i++)
    		for(u3 j=0;j<channel_num;j++)
    			data[i*channel_num+j]=tracks[j][i];

    }

    std::vector<Sound_Track<T>> to_track() const
    {
    	std::vector<Sound_Track<T>> track(channel_num);
    	for(u3 i=0;i<channel_num;i++)
    	{
    		track[i].sample_rate=sample_rate;
    		track[i].data.resize(sample_num());
    	}
    	if(channel_num==1)
		{
			memcpy(track[0].data.data(),data.data(),sample_num()*sizeof(T));
		}
		else if(channel_num==2)
		{
			for(u3 i=0;i<sample_num();i++)
			{
				track[0][i]=data[i*2];
				track[1][i]=data[i*2+1];
			}
		}
		else
		{
			for(u3 i=0;i<sample_num();i++)
    			for(u3 j=0;j<channel_num;j++)
    				track[i][j]=data[i*channel_num+j];
		}
    	return track;
    }

    u3 sample_num() const noexcept
    {
    	return data.size()/channel_num;
    }
};

using PCM_i0=PCM<s0>;
using PCM_i1=PCM<s1>;
using PCM_i2=PCM<s2>;
using PCM_f2=PCM<f2>;
using PCM_f3=PCM<f3>;

using PCMi=PCM_i1;
using PCMf=PCM_f2;


