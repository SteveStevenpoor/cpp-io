#include <io.h>
#include <vector>
#include <gtest/gtest.h>
#include <iostream>


TEST(string_reader_writer, Ctr) {
    StringReaderWriter rw{"world"};

    EXPECT_TRUE(rw.is_open());
    EXPECT_FALSE(rw.is_eof());
    EXPECT_EQ(rw.pos(), 0);
    EXPECT_EQ(rw.data(), (std::string)"world");
}

TEST(string_reader_writer, write_string) {
    StringReaderWriter rw{"world"};
    rw.write_string("Hello, ");

    EXPECT_EQ(rw.data(), (std::string)"Hello, world");
    EXPECT_EQ(rw.pos(), 7);
}

TEST(string_reader_writer, write_int) {
    StringReaderWriter rw{" is my group"};
    rw.write_int(23162);

    EXPECT_EQ(rw.data(), (std::string)"23162 is my group");
    EXPECT_EQ(rw.pos(), 5);
}

TEST(string_reader_writer, write_double) {
    StringReaderWriter rw{".. is the pi"};
    rw.write_double(3.141592);

    EXPECT_EQ(rw.data(), (std::string)"3.141592.. is the pi");
    EXPECT_EQ(rw.pos(), 8);
}

TEST(string_reader_writer, read_int) {
    StringReaderWriter rw{"12 a. m."};
    rw.write_string("The time is ");

    EXPECT_EQ(rw.data(), (std::string)"The time is 12 a. m.");
    EXPECT_EQ(rw.pos(), 12);

    EXPECT_EQ(12, rw.read_int());
    EXPECT_EQ(rw.pos(), 14);
    EXPECT_FALSE(rw.is_eof());
}

TEST(string_reader_writer, read_double) {
    StringReaderWriter rw{"3.141592"};
    rw.write_string("The pi is ");

    EXPECT_EQ(rw.data(), (std::string)"The pi is 3.141592");
    EXPECT_EQ(rw.pos(), 10);

    EXPECT_DOUBLE_EQ(3.141592, rw.read_double());
    EXPECT_EQ(rw.pos(), 18);
    EXPECT_TRUE(rw.is_eof());
}

TEST(string_reader_writer, read_string) {
    StringReaderWriter rw{"world\naboba"};
    rw.write_string("Hello, ");

    EXPECT_EQ("world", rw.read_string());
    EXPECT_EQ(rw.pos(), 12);
    EXPECT_FALSE(rw.is_eof());
}

TEST(file_reader_writer, ctr) {
    FileReaderWriter rw{"test_resourses/1_actual.txt"};

    EXPECT_TRUE(rw.is_open());
    EXPECT_FALSE(rw.is_eof());
}

TEST(file_reader_writer, read_int) {
    FileReaderWriter rw{"test_resourses/3_actual.txt"};

    EXPECT_EQ(rw.read_int(), 23162);
}

TEST(file_reader_writer, read_double) {
    FileReaderWriter rw{"test_resourses/4_actual.txt"};

    EXPECT_DOUBLE_EQ(rw.read_double(), 3.141592);
}

TEST(file_reader_writer, read_string) {
    FileReaderWriter rw{"test_resourses/1_actual.txt"};

    EXPECT_EQ(rw.read_string(), "Hello, world!\n");
}

TEST(file_reader_writer, write_string) {
    FileReaderWriter actual_rw{"test_resourses/2_actual.txt"};
    actual_rw.write_string("Hello, world!\n");
    actual_rw.set_begin();

    FileReaderWriter expected_rw("test_resourses/2_expected.txt");

    EXPECT_EQ(actual_rw.read_string(), expected_rw.read_string());
}

TEST(file_reader_writer, write_int) {
    FileReaderWriter actual_rw{"test_resourses/5_actual.txt"};
    actual_rw.write_string("My group is ");
    actual_rw.write_int(23162);
    actual_rw.set_begin();

    FileReaderWriter expected_rw("test_resourses/5_expected.txt");

    EXPECT_EQ(actual_rw.read_string(), expected_rw.read_string());
}

TEST(file_reader_writer, write_double) {
    FileReaderWriter actual_rw{"test_resourses/6_actual.txt"};
    actual_rw.write_string("The pi is ");
    actual_rw.write_double(3.141592);
    actual_rw.set_begin();

    FileReaderWriter expected_rw("test_resourses/6_expected.txt");

    EXPECT_EQ(actual_rw.read_string(), expected_rw.read_string());
}
