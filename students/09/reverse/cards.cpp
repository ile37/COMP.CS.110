#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id) {

    if(top_ == nullptr) {
        return false;
    }

    id = top_->data;

    std::shared_ptr<Card_data> card_to_be_removed = top_;

    if (card_to_be_removed->next == nullptr) {
        top_ = nullptr;
    } else {
        top_ = card_to_be_removed->next;
    }

    return true;
}

void Cards::reverse() {
    if(top_ == nullptr or top_->next == nullptr) {

    } else {
        std::shared_ptr<Card_data> top_card = top_;
        recursive_print(top_->next, top_);
        top_card->next = nullptr;
    }
}

void Cards::recursive_print(std::shared_ptr<Card_data> top,
                            std::shared_ptr<Card_data> top_behind) {
    if (top->next == nullptr) {
        top_ = top;
    } else {
        recursive_print(top->next, top);
    }
    top->next = top_behind;

}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp







