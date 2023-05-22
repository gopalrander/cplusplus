enum class HRESULT: int 
{ 
    E_POINTER = -1,
    SUCCESS = 1 
};

class SomeClass{
public: 
    SomeClass(int x): m_var(x) {};

    HRESULT GetInt(int* pnVar){
        if(!pnVar) return HRESULT::E_POINTER;

        *pnVar = m_var;
        return HRESULT::SUCCESS;
    }

private:
    int m_var;

};

int main()
{
  SomeClass sc { 10 };
  int nVar = 0;
  
  sc.GetInt(&nVar);
  // we forgot to check hresult for success
  // before do something with nVar.
  
  // It is sometimes left out at the code reviewers to catch this.
  // Can we enforce? YES! [[nodiscard]]
  
	return 0;
}