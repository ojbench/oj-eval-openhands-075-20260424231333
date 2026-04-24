#pragma once
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstddef>

class str {
private:
    char* data_;
    std::size_t len_;

    static std::size_t cstrlen(const char* s) {
        return s ? std::strlen(s) : 0ULL;
    }

    void assign_from_cstr(const char* s) {
        std::size_t L = cstrlen(s);
        char* nd = new char[L + 1];
        if (L) std::memcpy(nd, s, L);
        nd[L] = '\0';
        delete[] data_;
        data_ = nd;
        len_ = L;
    }

public:
    str() : data_(new char[1]{'\0'}), len_(0) {}

    str(const char& c) : data_(new char[2]), len_(1) {
        data_[0] = c;
        data_[1] = '\0';
    }

    // As required: rvalue const char* constructor and assignment
    str(const char*&& s_) : data_(nullptr), len_(0) { assign_from_cstr(s_); }
    str& operator=(const char*&& s_) { assign_from_cstr(s_); return *this; }

    // Additional overloads for lvalue non-const char*
    str(char* s_) : data_(nullptr), len_(0) { assign_from_cstr(s_); }
    str& operator=(char* s_) { assign_from_cstr(s_); return *this; }

    str(const str& other) : data_(new char[other.len_ + 1]), len_(other.len_) {
        if (len_) std::memcpy(data_, other.data_, len_);
        data_[len_] = '\0';
    }

    str& operator=(const str& other) {
        if (this == &other) return *this;
        char* nd = new char[other.len_ + 1];
        if (other.len_) std::memcpy(nd, other.data_, other.len_);
        nd[other.len_] = '\0';
        delete[] data_;
        data_ = nd;
        len_ = other.len_;
        return *this;
    }

    char& operator[](std::size_t pos) { return data_[pos]; }
    const char& operator[](std::size_t pos) const { return data_[pos]; }

    std::size_t len() const { return len_; }

    str join(const std::vector<str>& strs) const {
        if (strs.empty()) return str();
        std::size_t total = 0;
        for (const auto& s : strs) total += s.len_;
        std::size_t sep = len_;
        if (strs.size() > 1) total += sep * (strs.size() - 1);

        str res;
        delete[] res.data_;
        res.data_ = new char[total + 1];
        res.len_ = total;

        std::size_t pos = 0;
        for (std::size_t i = 0; i < strs.size(); ++i) {
            const auto& s = strs[i];
            if (s.len_) {
                std::memcpy(res.data_ + pos, s.data_, s.len_);
                pos += s.len_;
            }
            if (i + 1 < strs.size() && sep) {
                std::memcpy(res.data_ + pos, data_, sep);
                pos += sep;
            }
        }
        res.data_[total] = '\0';
        return res;
    }

    str slice(std::size_t l, std::size_t r) const {
        if (l > len_) l = len_;
        if (r > len_) r = len_;
        if (r < l) r = l;
        std::size_t L = r - l;
        str res;
        delete[] res.data_;
        res.data_ = new char[L + 1];
        res.len_ = L;
        if (L) std::memcpy(res.data_, data_ + l, L);
        res.data_[L] = '\0';
        return res;
    }

    ~str() { delete[] data_; }
};
