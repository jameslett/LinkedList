#pragma once

class Stack
{

private:
	class Element
	{
	public:
		Element(int val, Element* pLast)
			:
			val(val),
			pLast(pLast)
			
		{
			if( pLast != nullptr){
				index = pLast->index + 1;
			}
		}
		Element(const Element& src)
			:
			val(src.val)
		{
			if (src.pLast != nullptr)
			{
				pLast = new Element(*src.pLast);
			}
		}
		Element& operator=(const Element& rhs) {
			pLast = rhs.pLast;
			val = rhs.val;

		}
		int GetVal() const
		{
			return val;
		}
		Element* Disconnect()
		{
			auto pTemp = pLast;
			pLast = nullptr;
			return pTemp;
		}



		int CountElements() const
		{
			if (pLast != nullptr)
			{
				return pLast->CountElements() + 1;
			}
			else
			{
				return 1;
			}
		}
		int SumElements() {
			int count = CountElements();
			if ( count == 1){
				return val;
			}
			else if (count > 1) {
				return pLast->SumElements() + val;
			}
			else {
				return 0;
			}
		}

		int MultiplyElements() {
			int count = CountElements();

			if (count == 1) {
				return val;
			}
			else if (count > 1) {
				return pLast->MultiplyElements() * val;
			}
			else {
				return 0;
			}



		}
		~Element()
		{
			delete pLast;
			pLast = nullptr;

		}

		int val;
		int index = 0;
		Element* pLast = nullptr;
		Element* pNext = nullptr;
	};
public:
	class Iterator {
	public:
		Iterator() = default;
		Iterator(Element* pElement) :
			pElement(pElement)
		{}
		bool operator !=(Iterator rhs) {
			return pElement != rhs.pElement;


		}
		int& operator *() {
			return pElement->val;
		}
		Iterator operator --() {
			pElement = pElement->pLast;
			return *this;
		}
		Iterator operator ++() {
			pElement = pElement->pNext;
			return *this;
		}
		Element* GetElement() {
			return pElement;
		}
	private:
		Element* pElement = nullptr;

	};

	class ConstIterator
	{
	public:
		ConstIterator() = default;
		ConstIterator(const Element* pElement)
			:
			pElement(pElement)
		{}
		ConstIterator& operator--()
		{
			pElement = pElement->pLast;
			return *this;
		}
		const int& operator*() const
		{
			return pElement->val;
		}
		bool operator!=(ConstIterator rhs) const
		{
			return pElement != rhs.pElement;
		}
	private:
		const Element* pElement = nullptr;
	};
	Stack() = default;
	Stack(const Stack& src)
	{
		*this = src;
	}
	Stack& operator=(const Stack& src)
	{
		if (&src != this)
		{
			if (!Empty())
			{
				delete pTop;
				pTop = nullptr;
			}

			if (!src.Empty())
			{
				pTop = new Element(*src.pTop);
			}
		}
		return *this;
	}


		int operator[](int index) {
		Iterator it = Iterator(pTop);
		int size = Size();
		for (int i = 0; i < size; i++) {
			if (it.GetElement()->index != index) {
				--it;
			}
			else {
				return it.GetElement()->GetVal();
				break;
			}
		}
	}



	~Stack()
	{
		delete pTop;
		pTop = nullptr;
	}





	void Push(int val)
	{
		if (pTop != nullptr) {
			pTop->pNext = new Element(val, pTop);

			pTop = pTop->pNext;
		}
		else {
				pTop = new Element(val, pTop);
			}

	}

	int Sum() {
		return pTop->SumElements();
	}

	int MultiplyAll() {
		return pTop->MultiplyElements();
	}


	int Pop()
	{
		if (!Empty())
		{
			const int tempVal = pTop->GetVal();
			auto pOldTop = pTop;
			pTop = pTop->Disconnect();
			delete pOldTop;
			if (pTop != nullptr){
				pTop->pNext = nullptr;
			}
			
			return tempVal;
		}
		else
		{
			return -1;
		}
	}
	int Size() const
	{
		if (!Empty())
		{
			return pTop->CountElements();
		}
		else
		{
			return 0;
		}
	}



	bool Empty() const
	{
		return pTop == nullptr;
	}

	int TopValue() {
		return pTop->val;
	}

	Iterator begin() {
		if (pTop != nullptr) {
			Element* ele = pTop;
			while (ele->pLast != nullptr) {
				ele = ele->pLast;
			}

			return { ele };
		}
		else return pTop;

	}
	Iterator end() {
		return {pTop->pNext};
	}




private:
	Element* pTop = nullptr;
	



};