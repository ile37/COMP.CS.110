#include "queue.hh"
#include <iostream>

using namespace std;

Queue::Queue(unsigned int cycle): first_(nullptr), last_(nullptr), is_green_(false), cycle_(cycle) {
}

Queue::~Queue() {

    while (first_ != nullptr) {
        Vehicle* reg_to_be_released = first_;
        first_ = first_->next;

        delete reg_to_be_released;
    }
}

void Queue::enqueue(const string &reg) {

    if (is_green_) {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
    } else {
        Vehicle* new_reg = new Vehicle{reg, nullptr};
        new_reg->next = last_;
        last_ = new_reg;

        if (first_ == nullptr) {
            first_ = new_reg;
            first_->next = nullptr;
        }
    }
}

bool Queue::dequeue() {

    Vehicle* vehicle_to_be_released = first_;
    Vehicle* second_vehicle = last_;

    while (second_vehicle->next != first_) {
        second_vehicle = second_vehicle->next;
        if (second_vehicle == NULL) {
            break;
        }
    }

    first_ = second_vehicle;
    if (first_ != NULL) {
        first_->next = nullptr;
    }
    cout << vehicle_to_be_released->reg_num << " ";
    delete vehicle_to_be_released;

    if (first_ == nullptr) {
        return false;
    } else {
        return true;
    }
}

void Queue::switch_light() {


    if (first_ != NULL) {
        if (is_green_) {
            is_green_ = false;
        } else {
            cout << "GREEN: Vehicle(s) ";
            for (unsigned int i = 0; i < cycle_; ++i) {
                if (not dequeue()) {
                    break;
                }
            }
            cout << "can go on" << endl;
            is_green_ = false;
        }
    } else {

        if (is_green_) {
            is_green_ = false;
        } else {
            is_green_ = true;
        }
        print();
    }

}

void Queue::reset_cycle(unsigned int cycle) {

    cycle_ = cycle;
}

void Queue::print() const {
    if (first_ == NULL) {
        if (is_green_) {
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
        } else {
            cout << "RED: No vehicles waiting in traffic lights" << endl;
        }
    } else {
        if (is_green_) {
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
        } else {
            cout << "RED: Vehicle(s) ";
            recursive_print(last_);
            cout << "waiting in traffic lights" << endl;
        }
    }

}

void Queue::recursive_print(Vehicle* last) const{

    if (last->next != nullptr) {
        recursive_print(last->next);
    }
    cout << last->reg_num << " ";
}




