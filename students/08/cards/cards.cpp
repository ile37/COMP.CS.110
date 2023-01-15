#include "cards.hh"
#include <iostream>

Cards::Cards(): top_(nullptr) {

}


Card_data* Cards::get_topmost() {

    return top_;
}


void Cards::add(int id) {

    if(top_ == nullptr) {
        Card_data* new_card = new Card_data{id, nullptr};
        top_ = new_card;
    } else {
        Card_data* new_card = new Card_data{id, top_};
        top_ = new_card;
    }


}


void Cards::print_from_top_to_bottom(std::ostream & s) {

    Card_data* card_to_be_printed = top_;

    int running_number = 1;
    while (card_to_be_printed != nullptr) {
        s << running_number << ": " << card_to_be_printed->data << std::endl;
        card_to_be_printed = card_to_be_printed->next;
        running_number += 1;
    }
}


bool Cards::remove(int& id) {

    if(top_ == nullptr) {
        return false;
    }

    id = top_->data;

    Card_data* card_to_be_removed = top_;

    if (card_to_be_removed->next == nullptr) {
        top_ = nullptr;
    } else {
        top_ = card_to_be_removed->next;
    }

    delete card_to_be_removed;
    return true;
}


bool Cards::bottom_to_top() {

    if(top_ == nullptr) {
        return false;
    }

    Card_data* top_card = top_;
    Card_data* bottom_card_to_be = top_;

    while (bottom_card_to_be->next != nullptr) {

      top_card = top_card->next;
      bottom_card_to_be = top_card->next;
    }
    bottom_card_to_be->next = top_;
    // new last card
    top_card->next = nullptr;

    top_ = bottom_card_to_be;
    return true;

}


bool Cards::top_to_bottom() {

    if(top_ == nullptr) {
        return false;
    }

    Card_data* top_card = top_;
    Card_data* bottom_card_to_be;

    while (top_card != nullptr) {

        bottom_card_to_be = top_card;
        top_card = top_card->next;
    }

    top_card = top_;
    bottom_card_to_be->next = top_;
    top_ = top_card->next;
    top_card->next = nullptr;

    return true;

}


void Cards::print_from_bottom_to_top(std::ostream &s) {

    Card_data* card_to_be_printed = top_;

    int running_number = 1;
    while (card_to_be_printed != nullptr) {
        card_to_be_printed = card_to_be_printed->next;
        running_number += 1;
    }

    recursive_print(top_, s, running_number);
}


int Cards::recursive_print(Card_data *top, std::ostream & s, int running_num) {

    if (top != NULL and top->next == nullptr) {
        --running_num;
        s << running_num << ": " << top->data << std::endl;
        return running_num;
    } else if (top != NULL){
        --running_num;
        recursive_print(top->next,s, running_num);
        s << running_num << ": " << top->data << std::endl;
    }

    return running_num;
}


Cards::~Cards() {

    while (top_ != nullptr) {
        Card_data* card_to_be_released = top_;
        top_ = top_->next;

        delete card_to_be_released;
    }
}

