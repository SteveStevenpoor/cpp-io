#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cctype>
#include <sstream>

class IO {
protected:
    bool is_open_;
    bool is_eof_;

public:
    virtual bool is_open() const { return is_open_; }
    virtual bool is_eof() const { return is_eof_; }
    virtual void close() = 0;
};

class Reader : virtual public IO {
public:
    virtual int read_int() = 0;
    virtual double read_double() = 0;
    virtual std::string read_string() = 0;
};

class Writer : virtual public IO {
public:
    virtual void write_int(int value) = 0;
    virtual void write_double(double value) = 0;
    virtual void write_string(const std::string& value) = 0;
};

class ReaderWriter : public Reader, public Writer {
public:
    virtual void write_int(int value) override = 0;
    virtual void write_double(double value) override = 0;
    virtual void write_string(const std::string& value) override = 0;

    virtual int read_int() override = 0;
    virtual double read_double() override = 0;
    virtual std::string read_string() override = 0;
};

class StringReaderWriter : public ReaderWriter {
private:
    std::string data_;
    size_t pos_;

public:
    StringReaderWriter(const std::string& str) : data_(str), pos_(0) {
        is_open_ = true;
        is_eof_ = (pos_ == data_.length());
    }

    int pos() const { return pos_; }
    std::string data() const { return data_; }

    void close() override;

    int read_int() override;
    double read_double() override;
    std::string read_string() override;

    void write_int(int value) override;
    void write_double(double value) override;
    void write_string(const std::string& value) override;
};

class FileReaderWriter : public ReaderWriter {
private:
    FILE* f;
public:
    FileReaderWriter(std::string name, std::string mode = "r+") {
        f = fopen(name.c_str(), mode.c_str());
        if (f == nullptr) {
            is_open_ = false;
            is_eof_ = true;
        } else {
            is_open_ = true;
            is_eof_ = feof(f);
        }
    }

    ~FileReaderWriter() noexcept {
        if (f != nullptr) {
            fclose(f);
            is_open_ = false;
            is_eof_ = true;
        }
    }

    void close() override;

    int read_int() override;
    double read_double() override;
    std::string read_string() override;

    void write_int(int value) override;
    void write_double(double value) override;
    void write_string(const std::string& value) override;

    void set_begin() { rewind(f); }
    FILE* get_file() { return f; }
};

#endif // IO_H
