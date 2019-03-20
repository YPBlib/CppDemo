#include<initializer_list>
#include<ios>
#include<iostream>
#include<new>
#include<utility>
#include<memory>
using namespace std;
template <typename T> class Cycle_Linked_Node;
template <typename T> class Cycle_Linked_List;
template <typename T> class Fib_Heap;
template <typename T> class Fib_Node;
template <typename T> shared_ptr<Fib_Heap<T>> heap_union(shared_ptr<Fib_Heap<T>>H1, shared_ptr<Fib_Heap<T>>H2);

template <typename T>
class Cycle_Linked_Node
{
	friend class Cycle_Linked_List<T>;
public:
	shared_ptr<T> key = nullptr;
	shared_ptr <Cycle_Linked_Node<T>> left = nullptr;
	shared_ptr<Cycle_Linked_Node<T>> right = nullptr;
	Cycle_Linked_Node() = default;
	Cycle_Linked_Node(T s)
	{
		key = make_shared<T>(s);
	}
	Cycle_Linked_Node<T>& operator =(const Cycle_Linked_Node<T> a)
	{
		if (a.key != nullptr)
		{
			key = make_shared<T>();
			*key = *a.key;
		}
		if (a.left != nullptr)
		{
			left = make_shared<Cycle_Linked_Node<T>>();
			*left = *a.left;
		}
		if (a.right != nullptr)
		{
			right = make_shared<Cycle_Linked_Node<T>>();
			*right = *a.right;
		}
		return *this;
	}
};

template <typename T>
class Cycle_Linked_List  //  head <----------------> tail
{
	size_t size_ = 0;
	shared_ptr<Cycle_Linked_Node<T> > head = nullptr;

public:
	Cycle_Linked_List() = default;
	Cycle_Linked_List(Cycle_Linked_Node<T> n)
	{
		size_ = 1;
		head = make_shared<Cycle_Linked_Node<T>>();
		*head = n;
	}
	Cycle_Linked_List(initializer_list<const T> l)
	{
		if (l.size())
		{
			size_ = l.size();
			head = make_shared<Cycle_Linked_Node<T> >();
			head->key = make_shared<T>(*(l.begin()));
			//head = make_shared<decltype(*head)>(*l.begin());
			if (l.size() == 1)
			{
				head->left = head->right = head;
				return;
			}
			auto h = head;
			for (auto i = l.begin() + 1; i != l.end(); ++i)
			{
				h->right = make_shared<Cycle_Linked_Node<T> >();
				h->right->key = make_shared<int>(*i);
				h->right->left = h;
				h = h->right;
			}
			h->right = head;
			head->left = h;
		}
	}
	size_t size()const
	{
		return size_;
	}
	Cycle_Linked_List<T>& operator =(const Cycle_Linked_List<T> a)
	{
		if (a.head == nullptr)
		{
			head = make_shared<Cycle_Linked_Node<T>>();
			*head = *a.head;
		}
		size_ = a.size();
		return *this;
	}
	// not test yet
	void insert(T x)
	{
		auto s = make_shared<Cycle_Linked_List<T> >();
		auto l = Cycle_Linked_List<T>{ x };
		*s = l;
		concat(s);
	}
	// not test yet
	void push_back(T x)
	{
		auto ptr = make_shared<Cycle_Linked_Node<T>>();
		ptr->key = make_shared<T>();
		*ptr->key = x;
		ptr->left = head->left;
		ptr->right = head;
		head->left->right = ptr;
		head->left = ptr;
	}
	// not test yet
	void concat(shared_ptr<Cycle_Linked_List<T> >L)
	{
		if (L->size() == 0)
			return;
		if (size_ == 0)
		{
			*this = *L;
			return;
		}
		size_ += L->size();
		auto t = L->head->left;
		L->head->left = head->left;
		t->right = head;
		head->left->right = L->head;
		head->left = t;
	}
	bool empty() { return size_ == 0; }
	void enlarge()
	{
		head = make_shared<Cycle_Linked_Node<T>>();
	}
	template <class F>
	void traverse(F f)
	{
		if (!empty())
		{
			shared_ptr<Cycle_Linked_Node<T>> iter;
			iter = head;
			for (auto i = 0; i != size(); ++i)
			{
				f(*(iter->key));
				iter = iter->right;
			}
		}
	}
};

template <typename T>
class Fib_Node
{
	friend class Fib_Heap<T>;
	//friend shared_ptr<Fib_Heap<T>> heap_union(shared_ptr<Fib_Heap<T>>H1, shared_ptr<Fib_Heap<T>>H2);
public:
	T key;
	int degree = 0;
	bool mark = false;
	shared_ptr<Fib_Node<T>> p = nullptr;
	shared_ptr<Fib_Node<T>> left = nullptr;
	shared_ptr<Fib_Node<T>> right = nullptr;
	shared_ptr<Fib_Node<T>> child = nullptr;
	shared_ptr<Cycle_Linked_List<Fib_Node<T>>> ChildrenList = nullptr;
	Fib_Node() = default;
	Fib_Node(int a):key(a){}
	Fib_Node(const Fib_Node& a)
	{
		key = a.key;
		degree = a.degree;
		mark = a.mark;
		if (a.p != nullptr)
		{
			p = make_shared<Fib_Node<T>>();
			*p = *(a.p);
		}
		if (a.left != nullptr)
		{
			left = make_shared<Fib_Node<T>>();
			*left = *a.left;
		}
		if (a.right != nullptr)
		{
			right = make_shared<Fib_Node<T>>();
			*right = *a.right;
		}
		if (a.child != nullptr)
		{
			child = make_shared<Fib_Node<T>>();
			*child = *a.child;
		}
		if (a.ChildrenList != nullptr)
		{
			ChildrenList = make_shared<Cycle_Linked_List<Fib_Node<T>>>();
			*ChildrenList = *a.ChildrenList;
		}
		
	}
	Fib_Node<T>& operator =(const Fib_Node<T> a)
	{
		key = a.key;
		degree = a.degree;
		mark = a.mark;
		if (a.p != nullptr)
		{
			p = make_shared<Fib_Node<T>>();
			*p = *(a.p);
		}
		if (a.left != nullptr)
		{
			left=make_shared<Fib_Node<T>>();
			*left = *a.left;
		}
		if (a.right != nullptr)
		{
			right=make_shared<Fib_Node<T>>();
			*right = *a.right;
		}
		if (a.child != nullptr)
		{
			child=make_shared<Fib_Node<T>>();
			*child = *a.child;
		}
		if (a.ChildrenList != nullptr)
		{
			ChildrenList=make_shared<Cycle_Linked_List<Fib_Node<T>>>();
			*ChildrenList = *a.ChildrenList;
		}
		return *this;
	}
};

// not test yest
template <typename T>
class Fib_Heap
{
	//friend shared_ptr<Fib_Heap<T>> heap_union(shared_ptr<Fib_Heap<T>>H1, shared_ptr<Fib_Heap<T>>H2);
	
	shared_ptr<Fib_Node<T>> heapmin = nullptr;
	int n = 0;
	shared_ptr<Cycle_Linked_List<Fib_Node<T>>> RootList = nullptr;
public:
	Fib_Heap() :n(0), heapmin(nullptr) { RootList = make_shared<Cycle_Linked_List<Fib_Node<T>>>(); RootList->enlarge(); }
	Fib_Heap<T>& operator =(const Fib_Heap<T> a)
	{
		if (a.heapmin != nullptr)
		{
			heapmin = make_shared<Fib_Node<T>>();
			*heapmin = *a.heapmin;
		}
		n = a.n;
		if (a.RootList != nullptr)
		{
			RootList = make_shared<Cycle_Linked_List<Fib_Node<T>>>();
			*RootList = *a.RootList;
		}
	}
	void insert(shared_ptr<Fib_Node<T>> x);
	shared_ptr<Fib_Node<T>> Extract_Min();
	void Fib_Heap_Link(Fib_Heap<T> H, shared_ptr<Fib_Node<T>> y, shared_ptr<Fib_Node<T>> x);
	void consolidate(Fib_Heap<T> H);
	void cut(shared_ptr<Fib_Node<T>>x, shared_ptr<Fib_Node<T>> y);
	void cascading(shared_ptr<Fib_Node<T>> y);
	void Decrease_Key(shared_ptr<Fib_Node<T>> x, T k);
};

template <typename T>
void Fib_Heap<T>::insert(shared_ptr<Fib_Node<T>> x)
{
	x->degree = 0;
	x->mark = false;
	x->p = nullptr;
	x->child = nullptr;
	RootList->push_back(*x);
	if (heapmin == nullptr)
	{
		heapmin = x;
	}
	else
	{
		if (x->key < heapmin->key)
			heapmin = x;
	}
	n += 1;
}


template <typename T>
shared_ptr<Fib_Heap<T>> heap_union(shared_ptr<Fib_Heap<T>>H1, shared_ptr<Fib_Heap<T>>H2)
{
	auto H = make_shared<Fib_Heap<T>>();
	H->heapmin = H1->heapmin;
	H->RootList->concat((H2->RootList));
	if (H1->heapmin == nullptr or ((H2->heapmin not_eq nullptr) and ((H2->heapmin->key) < (H1->heapmin->key))))
	{
		H->heapmin = H2->heapmin;
	}
	H->n = H1->n + H2->n;
	return H;
}

template <typename T>
shared_ptr<Fib_Node<T>> Fib_Heap::Extract_Min()
{
	auto z = heapmin;
	if (z != nullptr)
	{
		auto l = z->ChildrenList;
		for (auto i = l->head, j = 0; j != l->size(); ++j)
		{
			RootList->push_back(*i);
			i->p = nullptr;
		}
		RootList->erase(RootList->find(z));
		if (z == z->right)
			heapmin = nullptr;
		else
		{
			heapmin = z->right;
			consolidate();
		}
		n -= 1;
	}
	return z;
}

template <typename T>
void Fib_Heap::Fib_Heap_Link(Fib_Heap<T> H, shared_ptr<Fib_Node<T>> y, shared_ptr<Fib_Node<T>> x)
{
	RootList->erase(RootList->find(y));
	x->ChildrenList->push_back(y);
	x->degree++;
}

template <typename T>
void Fib_Heap::consolidate(Fib_Heap<T> H)
{
	//auto A = make_shared<int[degree]>();
	auto A = make_shared<Cycle_Linked_List<shared_ptr<int>>();
	A->resize(n,nullptr);
	foreach(w, H->RootList)
	{
		;
	}
}

template <typename T>
void Fib_Heap::cut(shared_ptr<Fib_Node<T>>x, shared_ptr<Fib_Node<T>> y)
{
	;
}

template <typename T>
void Fib_Heap::cascading(shared_ptr<Fib_Node<T>> y)
{
	;
}

template <typename T>
void Fib_Heap::Decrease_Key(shared_ptr<Fib_Node<T>> x, T k)
{
	; 
}

void coutint(int a)
{
	cout << a << endl;
}

int main(void)
{
	Cycle_Linked_List<int> cc({ 1,2,3,4,5,6 });
	auto cc2=make_shared<decltype(cc)>();
	*cc2 = Cycle_Linked_List<int>({7,8,9});
	cc.concat(cc2);
	cc.insert(10);
	cc.traverse<decltype(coutint)>(coutint);
	Cycle_Linked_Node<int> ii;
	auto FNode = make_shared<Fib_Node<int>>(5);
	auto FHeap = make_shared<Fib_Heap<int>>();
	FHeap->insert(FNode);
	return 0;
}