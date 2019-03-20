#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<assert.h>
#define is ==

typedef struct BST bst;
typedef struct AVL avl;
typedef struct SPLAY splay;
void inorder(char* type, void* T);
void preorder(char* type, void* T);
int mymax(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	int i, max = va_arg(ap, int), tmp;
	for (i = 1; i < n; ++i)
		max = max >= (tmp = va_arg(ap, int)) ? max : tmp;
	va_end(ap);
	return max;
}

int max2(int a, int b)
{
	return a >= b ? a : b;
}

struct BST
{
	int key;
	bst* left;
	bst* right;
};

bst* bst_search(int x, bst const* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}
	if (T->key is x)
		return T;
	else if (x < T->key)
		return bst_search(x, T->left);
	else
		return bst_search(x, T->right);

}

bst* bst_insert(int x, bst* T)
{
	if (T is NULL)
	{
		T = (bst*)malloc(sizeof(bst));
		T->key = x;
		T->left = T->right = NULL;
		return T;
	}

	if (x < T->key)
		T->left = bst_insert(x, T->left);
	else if (x > T->key)
		T->right = bst_insert(x, T->right);
	else
	{
		fprintf(stderr, "duplicate keys insertion");
		exit(-1);
	}
	return T;
}

bst* bst_getmin(bst const* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR");
		exit(-1);
	}
	bst* tmp = T;
	while (tmp->left)
	{
		tmp = tmp->left;
	}
	return tmp;
}

bst* bst_delete(int x, bst* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}

	if (x < T->key)
		T->left = bst_delete(x, T->left);
	else if (x > T->key)
		T->right = bst_delete(x, T->right);
	else
	{
		if (T->left is NULL || T->right is NULL)
		{
			bst* tmp = T;
			(T->left is NULL) ? (T = T->right) : (T = T->left);
			free(tmp);
		}
		else
		{
			bst* tmp = bst_getmin(T->right);
			T->key = tmp->key;
			T->right = bst_delete(T->key, T->right);
		}
	}

	return T;
}

struct AVL
{
	int key;
	avl* left;
	avl* right;
	int height;
};

int avl_get_height(avl* T)
{
	return T ? T->height : 0;
}
int avl_set_height(avl* T)
{
	return T->height = 1 + max2(avl_get_height(T->left), avl_get_height(T->right));
}

//	      R                 R
//	     / \               / \
//	    T   1   LL(T)     A    1
//	   / \      ===>     / \
//	  A   2             4   T
//	 / \                   / \
//	4   3                 3   2
avl* avl_LL(avl* T)
{
	avl*  A = T->left;
	T->left = A->right;
	A->right = T;
	avl_set_height(T);
	avl_set_height(A);
	return A;
}
//	   R                    R
//    / \                  / \
//   1   T      RR(T)     1   A
// 	    / \     ===>         / \
//	   2   A                T   4
//		  / \              / \
//	     3   4            2   3
avl* avl_RR(avl* T)
{
	avl* A = T->right;
	T->right = A->left;
	A->left = T;
	avl_set_height(T);
	avl_set_height(A);
	return A;
}
//	     T                    T                    B
//      / \                  / \                  / \
//     A   4     RR(A)      B   4     LL(T)      /   \
//    / \        ===>      / \        ===>      A     T
//   1   B                A   3                / \   / \
//	    / \              / \                 1   2  3   4
//	   2   3            1   2
avl* avl_RL(avl* T)
{
	T->left = avl_RR(T->left);
	T = avl_LL(T);
	return T;
}
//	   T                    T                    B
//    / \                  / \                  / \
//   1   A        LL(A)   1   B       RR(T)    /   \
// 	    / \       ===>       / \      ===>    T     A
//	   B   4                2   A            / \   / \
//	  / \                      / \          1   2 3   4
//	 2   3                    3   4
avl* avl_LR(avl* T)
{
	T->right = avl_LL(T->right);
	T = avl_RR(T);
	return T;
}

avl* avl_search(int x, avl const* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}
	if (T->key is x)
		return T;
	else if (x < T->key)
		return avl_search(x, T->left);
	else
		return avl_search(x, T->right);
}

avl* avl_insert(int x, avl* T)
{
	if (T is NULL)
	{
		T = malloc(sizeof(avl));
		T->height = 1;
		T->left = T->right = NULL;
		T->key = x;
		return T;
	}
	if (x < T->key)
	{
		T->left = avl_insert(x, T->left);
		if (avl_get_height(T->left) - avl_get_height(T->right) > 1)
		{
			if (avl_get_height(T->left->left) > avl_get_height(T->left->right))
				T = avl_LL(T);
			else
				T = avl_RL(T);
		}
	}
	else if (x > T->key)
	{
		T->right = avl_insert(x, T->right);
		if (avl_get_height(T->right) - avl_get_height(T->left) > 1)
		{
			if (avl_get_height(T->right->right) > avl_get_height(T->right->left))
				T = avl_RR(T);
			else
				T = avl_LR(T);
		}
	}
	else
	{
		fprintf(stderr, "duplicate keys insertion");
		exit(-1);
	}
	avl_set_height(T);
	return  T;
}

avl* avl_getmin(avl const *T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR");
		exit(-1);
	}
	avl* tmp = T;
	while (tmp->left)
	{
		tmp = tmp->left;
	}
	return tmp;
}

avl* avl_delete_wrapper(int x, avl* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}

	if (x < T->key)
		T->left = avl_delete_wrapper(x, T->left);
	else if (x > T->key)
		T->right = avl_delete_wrapper(x, T->right);
	else
	{
		if (T->left is NULL || T->right is NULL)
		{
			avl* tmp = T;
			(T->left is NULL) ? (T = T->right) : (T = T->left);
			free(tmp);
		}
		else
		{
			avl* tmp = avl_getmin(T->right);
			T->key = tmp->key;
			T->right = avl_delete_wrapper(T->key, T->right);
		}
	}

	return T;
}

avl* avl_delete(int x, avl* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}

	if (x < T->key)
		T->left = avl_delete_wrapper(x, T->left);
	else if (x > T->key)
		T->right = avl_delete_wrapper(x, T->right);
	else
	{
		if (T->left is NULL || T->right is NULL)
		{
			avl* tmp = T;
			(T->left is NULL) ? (T = T->right) : (T = T->left);
			free(tmp);
		}
		else
		{
			avl* tmp = avl_getmin(T->right);
			T->key = tmp->key;
			T->right = avl_delete_wrapper(T->key, T->right);
		}
	}
	if (T is NULL)
		return T;
	avl_set_height(T);
	if (avl_get_height(T->left) - avl_get_height(T->right) > 1)
	{
		if (avl_get_height(T->left->left) > avl_get_height(T->left->right))
			T = avl_LL(T);
		else
			T = avl_RL(T);
	}
	else if (avl_get_height(T->right) - avl_get_height(T->left) > 1)
	{
		if (avl_get_height(T->right->right) > avl_get_height(T->right->left))
			T = avl_RR(T);
		else
			T = avl_LR(T);
	}
	return T;
}

struct SPLAY
{
	int key;
	splay* left;
	splay* right;
	splay* fa;
};

splay* splay_L(splay* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}
	if (T->fa is NULL)
	{
		fprintf(stderr, "too shallow, no need to call %s", __FUNCTION__);
		exit(-1);
	}
	splay* S = T->fa;

	if (S->fa)
	{
		if (S is S->fa->left)
			S->fa->left = T;
		else
			S->fa->right = T;
	}
	T->fa = S->fa;
	S->fa = T;
	if (T->right)
		T->right->fa = S;
	S->left = T->right;
	T->right = S;
	return T;
}

splay* splay_R(splay* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}
	if (T->fa is NULL)
	{
		fprintf(stderr, "too shallow, no need to call %s", __FUNCTION__);
		exit(-1);
	}
	splay* S = T->fa;
	if (S->fa)
	{
		if (S is S->fa->left)
			S->fa->left = T;
		else
			S->fa->right = T;
	}
	T->fa = S->fa;
	S->fa = T;
	if (T->left)
		T->left->fa = S;
	S->right = T->left;
	T->left = S;
	return T;
}

splay* splay_splay(splay* T)
{
	while (1)
	{
		if (T is NULL)
		{
			fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
			exit(-1);
		}
		if (T->fa is NULL)
			return T;
		if (T->fa->fa is NULL)
		{
			if (T is T->fa->left)
			{
				T = splay_L(T);
				return T;
			}
			else
			{
				T = splay_R(T);
				return T;
			}
		}
		if (T->fa is T->fa->fa->left)
		{
			if (T is T->fa->left) // LL
			{
				T->fa = splay_L(T->fa);
				T = splay_L(T);
			}
			else
			{
				T = splay_R(T);
				T = splay_L(T);
			}
		}
		else if (T is T->fa->left)
		{
			T = splay_L(T);
			T = splay_R(T);
		}
		else
		{
			T->fa = splay_R(T->fa);
			T = splay_R(T);
		}
	}
}

splay* splay_search_wrapper(int x, splay const* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}
	if (x < T->key)
		return splay_search_wrapper(x, T->left);
	else if (x > T->key)
		return splay_search_wrapper(x, T->right);
	else
		return T;
}

splay* splay_search(int x, splay* T)
{
	splay* tmp = splay_search_wrapper(x, T);

	tmp = splay_splay(tmp);
	return tmp;
}

splay* splay_insert_wrapper(int x, splay *T)
{
	if (T is NULL)
	{
		T = (splay*)malloc(sizeof(splay));
		T->key = x;
		T->fa = T->left = T->right = NULL;
		return T;
	}

	if (x < T->key)
	{
		T->left = splay_insert_wrapper(x, T->left);
		T->left->fa = T;
	}
	else if (x > T->key)
	{
		T->right = splay_insert_wrapper(x, T->right);
		T->right->fa = T;
	}
	else
	{
		fprintf(stderr, "duplicate keys insertion");
		exit(-1);
	}
	return T;
}

splay* splay_insert(int x, splay* T)
{
	T = splay_insert_wrapper(x, T);
	splay* tmp = splay_search_wrapper(x, T);
	return splay_splay(tmp);
}

splay* splay_getmin(splay const* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}
	while (T->left)
		T = T->left;
	return T;
}

splay* splay_getmax(splay const* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}
	while (T->right)
		T = T->right;
	return T;
}

splay* splay_delete(int x, splay* T)
{
	if (T is NULL)
	{
		fprintf(stderr, "NULL TREE ERROR when calling %s", __FUNCTION__);
		exit(-1);
	}
	T = splay_search(x, T);
	if (T->left is NULL || T->right is NULL)
	{
		splay* tmp = (T->left is NULL) ? T->right : T->left;
		tmp->fa = NULL;
		free(T);
		return tmp;
	}
	splay* tmp = splay_getmin(T->right);
	if (tmp is T->right)
	{
		tmp->fa = NULL;
		tmp->left = T->left;
		T->left->fa = tmp;
	}
	else
	{
		if (tmp->right)
			tmp->right->fa = tmp->fa;
		tmp->fa->left = tmp->right;
		tmp->fa->fa = tmp;
		tmp->right = tmp->fa;
		tmp->fa = NULL;

		tmp->left = T->left;
		if (T->left)
			T->left->fa = tmp;
	}
	free(T);
	return tmp;
}

union tree
{
	bst* bstT;
	avl* avlT;
	splay* splayT;
};

void inorder(char* type, void* T)
{
	if (T is NULL)
		return;
	union tree tmp;
	if (type is "bst")
	{
		tmp.bstT = (bst*)T;
		inorder(type, tmp.bstT->left);
		printf("%d ", tmp.bstT->key);
		inorder(type, tmp.bstT->right);
	}
	else if (type is "avl")
	{
		tmp.avlT = (avl*)T;
		inorder(type, tmp.avlT->left);
		printf("%d ", tmp.avlT->key);
		inorder(type, tmp.avlT->right);
	}
	else
	{
		tmp.splayT = (splay*)T;
		inorder(type, tmp.splayT->left);
		printf("%d ", tmp.splayT->key);
		inorder(type, tmp.splayT->right);
	}
}

void preorder(char* type, void* T)
{
	if (T is NULL)
		return;
	union tree tmp;
	if (type is "bst")
	{
		tmp.bstT = (bst*)T;
		printf("%d ", tmp.bstT->key);
		preorder(type, tmp.bstT->left);
		preorder(type, tmp.bstT->right);
	}
	else if (type is "avl")
	{
		tmp.avlT = (avl*)T;
		printf("%d ", tmp.avlT->key);
		preorder(type, tmp.avlT->left);
		preorder(type, tmp.avlT->right);
	}
	else
	{
		tmp.splayT = (splay*)T;
		printf("%d ", tmp.splayT->key);
		preorder(type, tmp.splayT->left);
		preorder(type, tmp.splayT->right);
	}
}

