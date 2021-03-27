#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

    void LinkedDequeue::Enqueue(Element e) {
        // TODO: напишите здесь свой код ...
        auto *new_node = new DoublyNode(e, nullptr, nullptr);
        if (size_ == 0) {
            front_ = new_node;
        } else {
            back_->previous = new_node;
            new_node->next = back_;
        }
        back_ = new_node;
        ++size_;
    }

    void LinkedDequeue::EnqueueFront(Element e) {
        // TODO: напишите здесь свой код ...
        auto *new_node = new DoublyNode(e, nullptr, nullptr);
        if (size_ == 0) {
            front_ = new_node;
            ++size_;
        } else {
            auto new_element = new DoublyNode(e, front_, nullptr);
            front_->next = new_element;
            front_ = new_element;
            ++size_;
        }
    }

    void LinkedDequeue::Dequeue() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }

        // TODO: напишите здесь свой код ...
        if (!(front_->previous)) {
            delete front_;
            front_ = nullptr;
            back_ = nullptr;
        } else {
            auto new_front = front_->previous;
            delete front_;
            front_ = new_front;
        }
        --size_;
    }

    void LinkedDequeue::DequeueBack() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }

        // TODO: напишите здесь свой код ...
        DoublyNode *deleted_node = back_;
        back_ = back_->next;
        if (back_ == nullptr) {
            front_ = nullptr;
        } else {
            back_->previous = nullptr;
        }
        delete deleted_node;
        --size_;
    }

    void LinkedDequeue::Clear() {
        // TODO: напишите здесь свой код ...
        for (DoublyNode *current_node = front_; current_node != nullptr;) {
            auto deleting_node = current_node;
            current_node = current_node->previous;
            delete deleting_node;
        }
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
    }

// === РЕАЛИЗОВАНО ===

    LinkedDequeue::~LinkedDequeue() {
        Clear();
    }

    std::optional<Element> LinkedDequeue::front() const {
        return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
    }

    std::optional<Element> LinkedDequeue::back() const {
        return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
    }

    bool LinkedDequeue::IsEmpty() const {
        return size_ == 0;
    }

    int LinkedDequeue::size() const {
        return size_;
    }

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

    std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
        os << "size: " << queue.size_ << '\n';
        for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
            if (current_node == queue.front_) os << "[FRONT] ";
            if (current_node == queue.back_) os << "[BACK] ";
            os << enum2str(current_node->data) << '\n';
        }
        return os;
    }

}  // namespace itis
