// CORE.Collection.h
//////////////////////////////////////////////////

#ifndef __CORE_COLLECTION_H_
#define __CORE_COLLECTION_H_

	template <class T>
	class Node {
	public:
		Node() {
			this->m_pNext = NULL;
			this->m_pPrev = NULL;
			this->m_pData = NULL;
		}

		Node *m_pNext, *m_pPrev;
		T* m_pData;
	};

	template <class T>
	class Collection {
		Node<T>* m_pCurrent;

	public:
		Node<T>* m_pRoot;

		Collection() {
			this->m_pCurrent = NULL;
			this->m_pRoot = NULL;
		}

		void _BeginEnumerate() {
			this->m_pCurrent = this->m_pRoot;
		}

		Node<T>* _GetNextNode() {
			Node<T>* pRet = this->m_pCurrent;
			if(this->m_pCurrent != NULL) {
				this->m_pCurrent = this->m_pCurrent->m_pNext;
			}
			return pRet;
		}

		T* _GetNextData() {
			Node<T>* pRet = this->m_pCurrent;
			if(this->m_pCurrent != NULL) {
				this->m_pCurrent = this->m_pCurrent->m_pNext;
			}
			return pRet != NULL ? pRet->m_pData : NULL;
		}
		
		void _Add(Node<T>* pNode) {
			if(pNode == NULL) return;
			if(this->m_pRoot == NULL) {
				this->m_pRoot = pNode;
			} else {
				Node<T>* pCurr = this->m_pRoot;
				while(pCurr->m_pNext != NULL) {
					pCurr = pCurr->m_pNext;
				}
				pCurr->m_pNext = pNode;
				pNode->m_pPrev = pCurr;
				pNode->m_pNext = NULL;
			}
		}

		void _Add(T* pData) {
			Node<T>* pNode = new Node<T>();
			if(pNode == NULL) return;

			pNode->m_pData = pData;
			this->_Add(pNode);
		}

		void _DeleteAll() {
			Node<T>* pCurr = this->m_pRoot;
			this->m_pRoot = NULL;

			while(pCurr != NULL) {
				Node<T>* pNext = pCurr->m_pNext;
				delete pCurr->m_pData;
				delete pCurr;
				pCurr = pNext;
			}
		}

		void _Remove(Node<T>* pNode) {
			if(pNode == NULL) return;
			Node<T>* pCurr = this->m_pRoot;
			while(pCurr != pNode && pCurr != NULL) {
				pCurr = pCurr->m_pNext;
			}
			if(pCurr == pNode) {
				if(this->m_pCurrent == pCurr) {
					this->m_pCurrent = pCurr->m_pNext;
				}
				if(pCurr->m_pPrev != NULL) {
					pCurr->m_pPrev->m_pNext = pCurr->m_pNext;
				}
				if(pCurr->m_pNext != NULL) {
					pCurr->m_pNext->m_pPrev = pCurr->m_pPrev;
				}
			}
		}

		void _Remove(T* pData) {
			if(pData == NULL) return;
			Node<T>* pCurr = this->m_pRoot;
			while(pCurr != NULL && pCurr->m_pData != pData) {
				pCurr = pCurr->m_pNext;
			}
			if(pCurr != NULL && pCurr->m_pData == pData) {
				if(pCurr == this->m_pRoot) {
					this->m_pRoot = pCurr->m_pNext;
				}
				if(pCurr->m_pPrev != NULL) {
					pCurr->m_pPrev->m_pNext = pCurr->m_pNext;
				}
				if(pCurr->m_pNext != NULL) {
					pCurr->m_pNext->m_pPrev = pCurr->m_pPrev;
				}
			}
		}
	};

#endif