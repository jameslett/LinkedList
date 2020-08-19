#pragma once
#include <string>
#include <optional>
template<typename T>
class Stack
{

private:
	template<typename T>
	class Element
	{

	public:
		Element(T val, Element* pLast)
			:
			val(val),
			pLast(pLast)

		{
			if (pLast != nullptr) {
				index = pLast->index + 1;
			}
		}
		Element(const Element& src)
			:
			val(src.val)
		{
			if (src.pLast != nullptr)
			{
				pLast = new Element<T>(*src.pLast);
			}
		}
		Element& operator=(const Element& rhs) {
			pLast = rhs.pLast;
			val = rhs.val;

		}
		T GetVal() const
		{
			return (T)val;
		}
		Element* Disconnect()
		{
			auto pTemp = pLast;
			pLast = nullptr;
			pNext = nullptr;
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

		~Element()
		{
			delete pLast;
			pLast = nullptr;
			pNext = nullptr;

		}

		T val;
		int index = 0;
		Element<T>* pLast = nullptr;
		Element<T>* pNext = nullptr;
	};
public:

	class Iterator {
	public:
		Iterator() = default;
		Iterator(Element<T>* pElement) :
			pElement(pElement)
		{}
		bool operator !=(Iterator rhs) {
			return pElement != rhs.pElement;


		}
		T& operator *() {
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
		Iterator operator + (int rhs) {
			for (int i = 0; i < rhs; i++) {
				pElement = pElement->pNext;
			}
			return pElement;
		}

		Iterator operator - (int rhs) {
			for (int i = 0; i < rhs; i++) {
				pElement = pElement->pLast;
			}

		}

		Element<T>* GetElement() {
			return pElement;
		}
	private:
		Element<T>* pElement = nullptr;

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


	T operator[](int index) {
		Iterator it = Iterator(pTop);
		int size = Size();

		if (size == 0 || index > pTop->index || index > 0) {
			std::cout << "INVALID INDEX";
		}
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





	void Push(T val)
	{
		if (pTop != nullptr) {
			pTop->pNext = new Element<T>(val, pTop);

			pTop = pTop->pNext;
		}
		else {
			pTop = new Element<T>(val, pTop);
		}

	}


	T Pop()
	{
		if (!Empty())
		{
			T tempVal = pTop->GetVal();
			auto pOldTop = pTop;
			pTop = pTop->Disconnect();
			delete pOldTop;
			if (pTop != nullptr) {
				pTop->pNext = nullptr;
			}

			return tempVal;
		}
		else
		{
			return T();
		}
	}

	void Erase(Iterator it) {


		Element<T>* next = it.GetElement()->pNext;
		Element<T>* last = it.GetElement()->pLast;
		if (last != nullptr) {
			last->Disconnect();

			last->pNext = next;
		}

		if (next != nullptr){
			next->pLast = last;
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

	T TopValue() {
		return pTop->val;
	}

	Iterator begin() {
		if (pTop != nullptr) {
			Element<T>* ele = pTop;
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
	Element<T>* pTop = nullptr;
	


};