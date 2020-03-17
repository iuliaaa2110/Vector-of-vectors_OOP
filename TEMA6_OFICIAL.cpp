#include<iostream>
using namespace std;

class vector{
    int nv;
    int *v;
    public:

        vector() {      ///constructor de initializare
            nv = 0;
            v = NULL;
        }
        vector(int n, int *w)
        {
            nv=n;
            v=w;
        }
        vector(vector &ob){  ///constructor de copiere
            nv=ob.nv;
            for(int i=1;i<=nv;i++)
                v[i]=ob.v[i];
        }
        ~vector()    ///destructor
        {
            delete &nv;
            delete &v;
        }

        friend vector operator + (vector &ob1,vector &ob2);
        friend class vectori_de_vectori;
        friend istream &operator >> (istream &i, vector &ob);
        friend ostream &operator << (ostream &o, vector &ob);
        public: int lungime_de_vector();
        public: int* vector_simplu(int l);
};

istream &operator >> ( istream &i,vector &ob)   /// >>
{
    cout<<"m=";
    i>>ob.nv;
    ob.v=new int[ob.nv+2];
    cout<<"cele m componente:";
    for(int j=1;j<=ob.nv;j++)
        i>>ob.v[j];
    return i;
}

ostream& operator << (ostream &o, vector &ob)  /// <<
{
   // o<<ob.nv<<'\n';
    for(int i=1;i<=ob.nv;i++)
        o<<ob.v[i]<<" ";
    return o;
}

 vector operator + (vector &ob1,vector &ob2)     /// + imi returneaza tot un obiect.
{
    vector ob3;
    ob3.nv=max(ob1.nv,ob2.nv);
    ob3.v=new int[ob3.nv+1];
    for(int i=1;i<=ob3.nv;i++)
    {
        ob3.v[i]=0;
        if(ob1.nv>=i)
            ob3.v[i]+=ob1.v[i];
        if(ob2.nv>=i)
            ob3.v[i]+=ob2.v[i];
    }
    return ob3;
}

int vector::lungime_de_vector()
{
    return this->nv;
}

int* vector::vector_simplu(int l)/// imi returneaza doar vectorul din obiect, adaptat la lungimea l.
{
    int *w;
    w=new int[l+1];
    for(int i=1;i<=l;i++)
    {
        if(i<=this->nv)
            w[i]=this->v[i];
        else
            w[i]=0;
    }
    return w;
}








class vectori_de_vectori
{
    int dim;
    vector *m;
    public:

    //supraincarcarea operatorilor:

    friend istream &operator >> (istream &i, vectori_de_vectori &ob);
    friend ostream &operator << (ostream &o, vectori_de_vectori &ob);
    friend int** &operator + (vectori_de_vectori &ob1,vectori_de_vectori &ob2);

    //metode:
    vectori_de_vectori() ///constructor de initializare basic
    {
        dim=1;
    }
    vectori_de_vectori(int n,int *c,int nr); ///initializare cu un nr pe n linii
    vectori_de_vectori(const vectori_de_vectori &ob);///copiere
    ~vectori_de_vectori(); ///destructor
    public: int** matrice();
    int i_max(vectori_de_vectori &ob2);
    int j_max(vectori_de_vectori &ob2);

};



vectori_de_vectori::vectori_de_vectori(int n,int *c,int nr)            ///constructor de initializare cu un nr pe n linii
{

    this->dim=n;
    this->m=new vector[dim+1];
    cout<<n<<" "<<this->dim<<endl;
    for(int i=1;i<=this->dim;i++)
    {
        m[i].v=new int[c[i]+1];
        this->m[i].nv=c[i];


        cout<<c[i]<<": ";           //verificare
        for(int j=1;j<=c[i];j++)
            {m[i].v[j]=nr;
            cout<<m[i].v[j]<<" ";
            }
        cout<<endl;
    }
    cout<<endl;

}

vectori_de_vectori::vectori_de_vectori(const vectori_de_vectori &ob)   ///constructor de copiere
{
    dim=ob.dim;
    for(int i=1;i<=ob.dim;i++)
        m[i]=ob.m[i];
}

istream &operator >> (istream &i,  vectori_de_vectori &ob)             ///>>
{
    cout<<"n=";
    i>>ob.dim;
    ob.m=new vector[ob.dim+1];
    for(int j=1;j<=ob.dim;j++)
        {
        i>>ob.m[j];
        }
    return i;
}

ostream &operator << (ostream &o, vectori_de_vectori &ob)              ///<<
{
   // cout<<ob.dim;
    for(int i=1;i<=ob.dim;i++)
    {
       // cout<<ob.m[i]<<" ";
        o<<ob.m[i]<<'\n';
    }
    return o;
}


int vectori_de_vectori::i_max(vectori_de_vectori &ob2)  ///i_max intre doua matrice
{
    if(this->dim>ob2.dim)
        return this->dim;
    return ob2.dim;
}

int vectori_de_vectori::j_max(vectori_de_vectori &ob2)  ///j_max dintre toate liniile din prima si din a doua matrice
{
    int max=0;
    for(int i=1;i<=this->dim;i++)
        if(this->m[i].lungime_de_vector()>max)
            max=this->m[i].lungime_de_vector();
      for(int i=1;i<=ob2.dim;i++)
        if(ob2.m[i].lungime_de_vector()>max)
            max=ob2.m[i].lungime_de_vector();
    return max;
}


int** vectori_de_vectori::matrice()         ///transform un vector de vectori in matrice
{
    int** a=new int*[this->dim+1];
    int jmax=this->j_max(*this);
    for(int i=1;i<=dim;i++)
    {
        a[i]=new int[jmax+1];
        a[i]=this->m[i].vector_simplu(jmax);

        for(int j=1;j<=jmax;j++)    //verificare
            cout<<a[i][j]<<" ";
        cout<<'\n';
    }
    return a;
}

int** &operator + (vectori_de_vectori &ob1,vectori_de_vectori &ob2)   ///adunarea intre 2 vectori de vectori, returnez o matrice.
{
    int imax=ob1.i_max(ob2);
    int jmax=ob1.j_max(ob2);
    cout<<imax<<" "<<jmax<<endl;
    int** a=new int*[imax+1];
    for(int i=1;i<=imax;i++)
    {
        a[i]=new int[jmax+1];
        if(ob1.dim<i)
            a[i]=(ob2.m[i]).vector_simplu(jmax);
        else if(ob2.dim<i)
                a[i]=(ob1.m[i]).vector_simplu(jmax);
        else
            a[i]=(ob1.m[i]+ob2.m[i]).vector_simplu(jmax);
        for(int j=1;j<=jmax;j++) //verificare
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    return a;
}



vectori_de_vectori::~vectori_de_vectori()                              ///destructor
{
    for(int i=1;i<=dim;i++)
        delete &m[i];
    delete &dim;
}

int main()
{

///1.CITIRE (SUPRAINCARCAREA LUI >>)
vectori_de_vectori ob2;
    cout<<'\n'<<'\n'<<"CITIRE:"<<'\n';
    cin>>ob2; //se vor citi: n=numarul de linii (numarul de vectori din vector)
                            //apoi de n ori cate un m si apoi cele m numere pentru linia i. (1<=i<=n)

    cout<<'\n'<<"Obiectul citit este:"<<'\n'<<ob2<<'\n'<<'\n';//verificare



///2.DECLARARE:
    int v[8]={0,1,2,3,4,5,6,7};//v[i]=numarul de componente pentru al i-lea vector din matrice
    cout<<"DECLARARE:"<<endl;
    vectori_de_vectori ob1(5,v,3);//am lasat afisari in initializare pt verificare



///3.AFISARE (SUPRAINCARCAREA LUI << )
    cout<<'\n'<<"AFISARE:"<<'\n'<<ob2<<'\n'<<'\n'<<ob1;//se afiseaza doar ob1.m si ob2.m, adica vectorii de vectori, nu si dimensiunile lor



///4.METODA DE TRANSFORMARE IN MATRICE
    cout<<'\n'<<"TRANSFORMAREA OBIECTULUI IN MATRICE:"<<endl;
    int **a=ob2.matrice(); //am pus afisarea in metoda, pentru verificare



///5.METODA DE ADUNARE A DOUA OBIECTE SI FURNIZAREA REZULTATULUI PRINTR-O MATRICE NORMALA
    cout<<'\n'<<"ADUNAREA CELOR DOUA MATRICI/E:"<<endl;
    int **b=ob1+ob2;


return 0;

}
