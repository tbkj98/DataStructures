#pragma once

#include <ostream>

namespace tbkj {

	constexpr char NULL_CHAR = '\0';

	class string {
	private:
		char* arr;
		size_t str_len;

		void init_arr(const char* arr) {
			this->str_len = length(arr);
			this->arr = new char[str_len + 1];
			for (size_t i = 0; i < str_len; ++i) {
				this->arr[i] = arr[i];
			}
			this->arr[str_len] = NULL_CHAR;
		}

		void init_arr() {
			char* arr = new char[1];
			arr[0] = NULL_CHAR;
			init_arr(arr);
			delete[] arr;
		}
	public:
		string(const char* arr) {
			if (arr == nullptr) {
				init_arr();
				return;
			}
			
			this->init_arr(arr);
		}

		string(const string& str): string(str.arr) { }
		~string() {
			delete[] arr;
		}

		char at(size_t position) const {
			if (position >= str_len) {
				return NULL_CHAR;
			}

			return arr[position];
		}

		bool empty() const {
			return size() == 0;
		}

		bool not_empty() const {
			return size() != 0;
		}

		size_t size() const {
			return str_len;
		}

		friend std::ostream& operator << (std::ostream& out, const tbkj::string str) {
			out << str.arr;
			return out;
		}

		bool operator ==(tbkj::string& other) const {
			if (size() != other.size()) {
				return false;
			}

			for (size_t i = 0; i < size(); ++i) {
				if (at(i) != other.at(i)) {
					return false;
				}
			}
			return true;
		}

		string operator =(tbkj::string& other) const {
			return string(other);
		}

		string operator =(const char* other) const {
			return string(other);
		}

		string operator +(tbkj::string& other) const {
			return concat(other);
		}

		string operator +(const char* other) const {
			string temp = string(other);
			return concat(temp);
		}

		string concat(tbkj::string& other) const {
			if (other.empty() && empty()) {
				return string(nullptr);
			}

			if (other.empty() && not_empty()) {
				return string(arr);
			}

			if (other.not_empty() && empty()) {
				return string(other.arr);
			}

			size_t new_length = size() + other.size();
			char* new_arr = new char[ new_length + 1];

			for (size_t i = 0; i < size(); ++i) {
				new_arr[i] = at(i);
			}

			for (size_t i = 0; i < other.size(); ++i) {
				new_arr[size() + i] = other.at(i);
			}

			new_arr[new_length] = NULL_CHAR;
			string str = string(new_arr);
			delete[] new_arr;
			return str;
		}

		static size_t length(const char* arr) {
			size_t length = 0;
			if (arr == nullptr) {
				return length;
			}

			for (length = 0; arr[length]; ++length);
			return length;
		}
	};
}