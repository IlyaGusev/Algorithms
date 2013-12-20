#ifndef TREAP_HPP_INCLUDED
#define TREAP_HPP_INCLUDED

template <class Key, class Priority, class CKey, class CPriority>
    void Treap<Key, Priority, CKey, CPriority>::build(vector<Priority>& data) noexcept{
        shared_ptr<Node> last(nullptr);
        for (int i=0; i<data.size(); i++){
            shared_ptr<Node> current(new Node(i, data[i]));
            if (last.get()==nullptr)
                _root = current;
            else{
                if (CPriority()(last->_priority, current->_priority)){
                    last->_right = current;
                    last->_right->_parent = static_cast<weak_ptr<Node>>(last);
                }
                else{
                    while (!CPriority()(last->_priority, current->_priority)){
                        last = last->_parent.lock();
                        if (last.get()==nullptr){
                            break;
                        }
                    }
                    if (last.get()==nullptr){
                        shared_ptr<Node> temp = _root;
                        _root = current;
                        _root->_left = temp;
                        _root->_left->_parent = static_cast<weak_ptr<Node>>(_root);
                    }
                    else{
                        shared_ptr<Node> temp = last->_right;
                        last->_right = current;
                        current->_parent = static_cast<weak_ptr<Node>>(last);
                        last->_right->_left = temp;
                        temp->_parent = static_cast<weak_ptr<Node>>(current);
                    }
                }
            }
            last = current;
        }
    }

template <class Key, class Priority, class CKey, class CPriority>
    shared_ptr<typename Treap<Key, Priority, CKey, CPriority>::Node>
    Treap<Key, Priority, CKey, CPriority>::merge(shared_ptr<Node> root_left, shared_ptr<Node> root_right) noexcept{
        if (root_left.get()==nullptr) return root_right;
        if (root_right.get()==nullptr) return root_left;

        if (CPriority()(root_left->_priority, root_right->_priority)){
            shared_ptr<Node> new_root = root_left;
            shared_ptr<Node> _right = merge(root_left->_right, root_right);
            new_root->_right = _right;
            return new_root;
        }
        else{
            shared_ptr<Node> new_root = root_right;
            shared_ptr<Node> _left = merge(root_left, root_right->_left);
            new_root->_left = _left;
            return new_root;
        }
    }

template <class Key, class Priority, class CKey, class CPriority>
    shared_ptr<typename Treap<Key, Priority, CKey, CPriority>::Node>
    Treap<Key, Priority, CKey, CPriority>::split(shared_ptr<Node> current, Key k) noexcept{
        if (current.get()==nullptr) return shared_ptr<Node>(new Node());
        shared_ptr<Node> dummy(new Node);
        shared_ptr<Node> s(new Node);
        if (CKey()(current->_key, k))
        {
            if (current->_right.get() == nullptr)
                dummy->_right = shared_ptr<Node>(nullptr);
            else
                s = split(current->_right, k);

            dummy->_right = s->_right;
            dummy->_left = current;
            dummy->_left->_left = current->_left;
            dummy->_left->_right = s->_left;
        }
        else
        {
            if (current->_left.get() == nullptr)
                dummy->_left = shared_ptr<Node>(nullptr);
            else
                s = split(current->_left, k);

            dummy->_left = s->_left;
            dummy->_right = current;
            dummy->_right->_left = s->_right;
            dummy->_right->_right = current->_right;
        }
        return dummy;
    }

template <class Key, class Priority, class CKey, class CPriority>
    void Treap<Key, Priority, CKey, CPriority>::split(Key k) noexcept{
        _root = split(_root, k);
    }

template <class Key, class Priority, class CKey, class CPriority>
    void Treap<Key, Priority, CKey, CPriority>::merge(Treap& other) noexcept{
        _root = merge(_root, other._root);
        other.clear();
    }

template <class Key, class Priority, class CKey, class CPriority>
    void Treap<Key, Priority, CKey, CPriority>::print(shared_ptr<Node> current = nullptr, int h = 0, bool started = false) const noexcept{
        if (current==nullptr && _root != nullptr && !started)
            current = _root;
        started = true;
        if (current!=nullptr){
            for (int i=0; i<h; i++)
                cout<<"  ";
            if (current->_parent.lock().get()!= nullptr){
                if (current->_parent.lock()->_left.get()==current.get()) cout<<"L: "; else cout<<"R: ";}
            else
                cout<<"r: ";
            cout<<current->_key<<"("<<current->_priority<<")"<<endl;
            print(current->_left, h+1, started);
            print(current->_right, h+1, started);
        }
    }

template <class Key, class Priority, class CKey, class CPriority>
    void Treap<Key, Priority, CKey, CPriority>::insert(Key __key, Priority __priority) noexcept{
        shared_ptr<Node> new_node(new Node(__key, __priority));
        shared_ptr<Node> dummy = split(_root, __key);
        _root = merge(merge(dummy->_left, new_node), dummy->_right);
    }

template <class Key, class Priority, class CKey, class CPriority>
    void Treap<Key, Priority, CKey, CPriority>::erase(Key __key) noexcept{
        shared_ptr<Node> dummy = split(_root, __key);
        shared_ptr<Node> dummy2 = split(dummy->_right, __key+1);
        _root = merge(dummy->_left, dummy2->_right);
    }

template <class Key, class Priority, class CKey, class CPriority>
    shared_ptr<typename Treap<Key, Priority, CKey, CPriority>::Node> Treap<Key, Priority, CKey, CPriority>::minimum() const noexcept{
        shared_ptr<Node> current = _root;
        while (current->_left!=nullptr)
            current = current->_left;
        return current;
    }

template <class Key, class Priority, class CKey, class CPriority>
    shared_ptr<typename Treap<Key, Priority, CKey, CPriority>::Node> Treap<Key, Priority, CKey, CPriority>::maximum() const noexcept{
        shared_ptr<Node> current = _root;
        while (current->_right!=nullptr)
            current = current->_right;
        return current;
    }

template <class Key, class Priority, class CKey, class CPriority>
    void Treap<Key, Priority, CKey, CPriority>::clear() noexcept{
       _root = shared_ptr<Node>(nullptr);
    }

#endif // TREAP_HPP_INCLUDED
