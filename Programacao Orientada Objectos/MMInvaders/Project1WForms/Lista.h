#pragma once

template <class T>
class NO
{
	T *Info;
	NO<T> *Prox;
public:
	NO(T *obj, NO<T> *Seg = NULL)
	{
		Info = obj;
		Prox = Seg;
	}
	NO<T> *GetProximo() { return Prox; }
	T *GetInfo() { return Info; }
};

template <class T>
class Lista
{
	NO<T> *Inicio;

public:
	Lista(void)
	{
		Inicio = NULL;
	}
	~Lista(void)
	{
		NO<T> *Frente;
		NO<T> *p = Inicio;
		while (p)
		{
			delete p->GetInfo();
			Frente = p->GetProximo();
			delete p;
			p = Frente;
		}
	}
	void Add(T *X)
	{
		Inicio = new NO<T>(X, Inicio);
	}
	int Contar()
	{
		int cont = 0;
		NO<T> *p = Inicio;
		while (p)
		{
			cont++;
			p = p->GetProximo();
		}
		return cont;
	}

	void Mostrar()
	{
		NO<T> *p = Inicio;
		while (p)
		{
			p->GetInfo()->Mostrar();
			p = p->GetProximo();
		}
	}

	bool Pertence(T *Obj)
	{
		NO<T> *p = Inicio;
		while (p)
		{
			T *X = p->GetInfo();
			if ((X == Obj) || (*X == *Obj)) return true;
			p = p->GetProximo();
		}
		return false;
	}
};

