#pragma once
#include <string>

constexpr int INITIAL_CAPACITY = 10;
constexpr float UPPER_BOUND_LOAD_FACTOR = 0.75f;
constexpr float LOWER_BOUND_LOAD_FACTOR = 0.05f;

class MapItem {
private:
	const std::string key;
	const std::string value;


public:
	MapItem(std::string key, std::string value) : key(key), value(value) {}

	std::string get_key() const {
		return key;
	}

	std::string get_value() const {
		return value;
	}
};

class Map {
private:
	int current_size;
	int current_capacity;
	MapItem** container;

public:
	Map() {
		this->current_size = 0;
		this->current_capacity = INITIAL_CAPACITY;
		init_container();
	}

	void add(std::string key, std::string value) {
		if (key.empty()) {
			return;
		}
		if (is_overload()) {
			re_hash_increase();
		}

		int container_index = hash(key);

		if (contains(key)) {
			remove(key);
		}

		MapItem* item = new MapItem(key, value);
		container[container_index] = item;
		current_size++;
	}

	void remove(std::string key) {
		if (key.empty() || not_contains(key)) {
			return;
		}

		int container_index = hash(key);
		MapItem* item = container[container_index];

		container[container_index] = nullptr;
		current_size--;
		delete item;

		if (is_underload()) {
			re_hash_decrease();
		}
	}

	std::string get(std::string key) const {
		int container_index = hash(key);
		MapItem* item = container[container_index];
		if (item == nullptr) {
			throw std::exception("No value exists");
		}
		return item->get_value();
	}

	bool contains(std::string key) const {
		int container_index = hash(key);
		MapItem* item = container[container_index];
		return item != nullptr;
	}

	bool not_contains(std::string key) const {
		return !contains(key);
	}

	bool is_empty() const {
		return current_size == 0;
	}

	int size() const {
		return current_size;
	}

	~Map() {
		for (int i = 0; i < current_capacity; ++i) {
			MapItem* item = container[i];
			if (item == nullptr) {
				continue;
			}

			container[i] = nullptr;
			delete item;
		}

		delete[]container;
	}

private:
	void init_container() {
		this->container = new MapItem * [current_capacity];
		for (int i = 0; i < current_capacity; ++i) {
			container[i] = nullptr;
		}
	}
	void add(MapItem* item) {
		if (item == nullptr) {
			return;
		}

		add(item->get_key(), item->get_value());
	}

	int hash(std::string& val) const {
		int result = 7;
		for (char ch : val) {
			result += 31 * ch;
		}
		result = result % current_capacity;
		return result;
	}

	bool is_overload() const {
		float threshold_load_factor = UPPER_BOUND_LOAD_FACTOR;
		float current_load_factor = current_size * 1.0f / current_capacity;
		return current_load_factor >= threshold_load_factor;
	}

	bool is_underload() const {
		if (current_capacity == INITIAL_CAPACITY) {
			return false;
		}
		float threshold_load_factor = LOWER_BOUND_LOAD_FACTOR;
		float current_load_factor = current_size * 1.0f / current_capacity;
		return current_load_factor <= threshold_load_factor;
	}

	void re_hash_increase() {
		// Saving old capacity
		int old_capacity = current_capacity;

		// Making current_container to be old container
		// so that current data can be transfer to new and 
		// it can be deleted later
		MapItem** old_container = container;

		increase_capacity();
		transfer_item_from_old_to_new_container(old_container, old_capacity);
		delete old_container;
	}

	void re_hash_decrease() {
		// Saving old capacity
		int old_capacity = current_capacity;

		// Making current_container to be old container
		// so that current data can be transfer to new and 
		// it can be deleted later
		MapItem** old_container = container;

		decrease_capacity();
		transfer_item_from_old_to_new_container(old_container, old_capacity);
		delete old_container;
	}


	void transfer_item_from_old_to_new_container(MapItem** old_container, int old_capacity) {
		for (int i = 0; i < old_capacity; ++i) {
			MapItem* item = old_container[i];
			if (item == nullptr) {
				continue;
			}

			add(item);
			delete item;
		}
	}

	/*
	* Increasing the container size
	*/
	void increase_capacity() {
		// Doubling the container capacity
		current_capacity = current_capacity * 2;
		// Initialising new container
		init_container();
		// Resetting the size
		current_size = 0;
	}

	/*
	* Decreasing the container size
	*/
	void decrease_capacity() {
		// Halfing the container capacity
		current_capacity = current_capacity / 2;
		// Initialising new container
		init_container();
		// Resetting the size
		current_size = 0;
	}

};