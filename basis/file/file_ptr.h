#pragma once

struct File
{
	File(const File&)=delete;
	File(File&&file2) noexcept:fp(file2.fp),file_name(file2.file_name),r(file2.r),w(file2.w),b(file2.b){file2.fp=nullptr;}
	File(std::string_view file_name,const char*mode):file_name(file_name)
	{
		fp=fopen(file_name.data(),mode);
		cu_assert(fp,"file {} not found.",file_name);

		for(s3 i=0;mode[i];i++)
		{
			if(mode[i]=='b')b=true;
			if(mode[i]=='r')r=true;
			if(mode[i]=='w')w=true;
		}
	};
	File& operator=(const File&file)=delete;
	File& operator=(File&&file) noexcept
	{
		if(this==&file)return *this;

		fclose(fp);
		fp=file.fp;
		file_name=(std::string&&)file.file_name;
		file.fp=nullptr;
		r=file.r;
		w=file.w;
		b=file.b;
		return *this;
	}

	std::vector<byte> read_all_bytes() const
	{
		cu_assert(this->r&&this->b,"Open mode must be rb for file: {}",file_name);
        // 保存当前位置
        long original_pos = ftell(fp);
        cu_assert(original_pos != -1, "Failed to get current file position for file: {}", file_name);
        
        // 移动到文件末尾获取文件大小
        cu_assert(fseek(fp, 0, SEEK_END) == 0, "Failed to seek to end of file: {}", file_name);
        long file_size = ftell(fp);
        cu_assert(file_size != -1, "Failed to get file size for file: {}", file_name);
        
        // 如果文件为空，返回空向量
        if (file_size == 0) {
            // 恢复原位置
            fseek(fp, original_pos, SEEK_SET);
            return {};
        }
        
        // 回到文件开头
        cu_assert(fseek(fp, 0, SEEK_SET) == 0, "Failed to seek to beginning of file: {}", file_name);
        
        // 读取文件内容
        std::vector<byte> buffer(file_size);
        size_t bytes_read = fread(buffer.data(), 1, file_size, fp);
        cu_assert(bytes_read == static_cast<size_t>(file_size), 
                  "Failed to read entire file: {}. Expected {} bytes, but read {} bytes.", 
                  file_name, file_size, bytes_read);
        
        // 恢复原位置
        fseek(fp, original_pos, SEEK_SET);
        
        return buffer;
	}

	std::string read_all_text() const
	{
		cu_assert(this->r&&!this->b, "File must be opened in read mode for file: {}", file_name);
		
		// 保存当前位置
		long original_pos = ftell(fp);
		cu_assert(original_pos != -1, "Failed to get current file position for file: {}", file_name);
		
		// 移动到文件末尾获取文件大小
		cu_assert(fseek(fp, 0, SEEK_END) == 0, "Failed to seek to end of file: {}", file_name);
		long file_size = ftell(fp);
		cu_assert(file_size != -1, "Failed to get file size for file: {}", file_name);
		
		// 如果文件为空，返回空字符串
		if (file_size == 0) {
			fseek(fp, original_pos, SEEK_SET);
			return "";
		}
		
		// 回到文件开头
		cu_assert(fseek(fp, 0, SEEK_SET) == 0, "Failed to seek to beginning of file: {}", file_name);
		
		// 读取文件内容到字符串
		std::string content;
		content.resize(file_size);
		
		size_t bytes_read = fread(content.data(), 1, file_size, fp);
		cu_assert(bytes_read == static_cast<size_t>(file_size), 
				  "Failed to read entire file: {}. Expected {} bytes, but read {} bytes.", 
				  file_name, file_size, bytes_read);
		
		// 恢复原位置
		fseek(fp, original_pos, SEEK_SET);
		
		return content;
	}

	operator FILE*() noexcept {return fp;}
	std::string_view name() const noexcept{return file_name;}

	~File() noexcept {fclose(fp);}

private:
	FILE*fp;
	bool r=false;
	bool w=false;
	bool b=false;
	std::string file_name;
};
