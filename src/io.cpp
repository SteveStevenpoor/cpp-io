#include <io.h>

void StringReaderWriter::close() {
    if (is_open_) {
        data_.clear();
        pos_ = 0;
        is_open_ = false;
        is_eof_ = true;
    }
}

int StringReaderWriter::read_int() {
    if (!is_open_) {
        throw "String is closed";
    }
    size_t int_len = 0;
    int res = std::stoi(data_.substr(pos_), &int_len);
    pos_ += int_len;
    is_eof_ = (pos_ == data_.length());
    return res;
}

double StringReaderWriter::read_double() {
    if (!is_open_) {
        throw "String is closed";
    }
    size_t double_len = 0;
    double res = std::stod(data_.substr(pos_), &double_len);
    pos_ += double_len;
    is_eof_ = (pos_ == data_.length());
    return res;
}

std::string StringReaderWriter::read_string() {
    if (!is_open_) {
        throw "String is closed";
    }
    std::string line;
    std::istringstream iss(data_.substr(pos_));
    std::getline(iss, line, '\n');
    pos_ += line.length();
    is_eof_ = (pos_ == data_.length());
    return line;
}

void StringReaderWriter::write_string(const std::string& value) {
    if (!is_open_) {
        throw "String is closed";
    }
    data_.insert(pos_, value);
    pos_ += value.length();
}

void StringReaderWriter::write_int(int value) {
    write_string(std::to_string(value));
}

void StringReaderWriter::write_double(double value) {
    write_string(std::to_string(value));
}

void FileReaderWriter::close() {
    if (is_open_) {
        if (f != nullptr) {
            fclose(f);
            is_open_ = false;
            is_eof_ = true;
        }
    }
}

int FileReaderWriter::read_int() {
    if (!is_open_) {
        throw "File is closed";
    }
    int res = 0;
    fscanf(f, "%i", &res);
    return res;
}

double FileReaderWriter::read_double() {
    if (!is_open_) {
        throw "File is closed";
    }
    double res = 0;
    fscanf(f, "%lf", &res);
    return res;
}

std::string FileReaderWriter::read_string() {
    if (!is_open_) {
        throw "File is closed";
    }
    char line[256];
    // fscanf(f, "%s", &line);
    fgets(line, 256, f);
    return std::string{line};
}

void FileReaderWriter::write_string(const std::string& value) {
    if (!is_open_) {
        throw "File is closed";
    }
    fprintf(f, "%s", value.c_str());
    fflush(f);
}

void FileReaderWriter::write_int(int value) {
    write_string(std::to_string(value));
}

void FileReaderWriter::write_double(double value) {
    write_string(std::to_string(value));
}