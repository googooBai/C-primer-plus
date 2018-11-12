#include<iostream>
#include<string>


namespace Abstr_emp
{
	using std::string;
	
	class abstr_emp
	{
	private:
		std::string fname;
		std::string lname;
		std::string job;
	public:
		abstr_emp() { fname = "noname"; lname = "noname"; job = "no job"; }
		abstr_emp(const string& fn, const string& ln, const string& j):fname(fn),lname(ln),job(j){}
		virtual void ShowAll() const;
		virtual void SetAll();
		friend std::ostream& operator<<(std::ostream &os, const abstr_emp &e);
		virtual ~abstr_emp() = 0{}
	};

	class employee :public abstr_emp
	{
	public:
		employee() :abstr_emp() {}
		employee(const string& fn, const string& ln, const string& j):abstr_emp(fn,ln,j){}
		~employee(){}
		virtual void ShowAll() const;
		virtual void SetAll() ;
	};

	class manager :virtual public abstr_emp
	{
	private:
		int inchargeof;
	protected:
		int InChargeOf() const { return inchargeof; }
		int& InChargeOf() { return inchargeof; }
	public:
		manager():abstr_emp(),inchargeof(0){}
		manager(const string& fn, const string &ln, const string& j, int ico = 0):abstr_emp(fn,ln,j),inchargeof(ico){}
		manager(const abstr_emp& e, int ico) :abstr_emp(e),inchargeof(0){}
		manager(const manager& m) :abstr_emp(m),inchargeof(m.inchargeof){}
		~manager(){}
		virtual void ShowAll() const;
		virtual void SetAll();
	};

	class fink :virtual public abstr_emp
	{
	private:
		string reportsto;
	protected:
		string ReportsTo() const { return reportsto; }
		string& ReportsTo() { return reportsto; }	
	public:
		fink() :abstr_emp(),reportsto("no reprots"){}
		fink(const string& fn, const string &ln, const string& j, const string& rpo):abstr_emp(fn,ln,j),reportsto(rpo){}
		fink(const abstr_emp& e, const string& rpo):abstr_emp(e),reportsto(rpo){}
		fink(const fink& e):abstr_emp(e),reportsto(e.reportsto){}
		~fink(){}
		virtual void ShowAll() const;
		virtual void SetAll();
	};

	class highfink:public manager,public fink
	{
	public:
		highfink() :abstr_emp(), manager(), fink() {  }
		highfink(const string& fn, const string &ln, const string& j, const string& rpo, int ico) :abstr_emp(fn, ln, j), manager(fn, ln, j, ico), fink(fn, ln, j, rpo) {}
		highfink(const abstr_emp& e, const string& rpo, int ico):abstr_emp(e),manager(e,ico),fink(e,rpo){}
		highfink(const fink& f, int ico):abstr_emp(f),fink(f),manager(f,ico){}
		highfink(const manager& m, const string& rpo):abstr_emp(m),manager(m),fink(m,rpo){}
		highfink(const highfink& h): abstr_emp(h), manager(h), fink(h) {}
		~highfink(){}
		virtual void ShowAll() const;
		virtual void SetAll();
	};

	void abstr_emp::ShowAll() const
	{
		using std::cout;
		using std::endl;
		cout << "First name: " << fname << endl;
		cout << "Last name: " << lname << endl;
		cout << "Job: " << job << endl;
	}

	void abstr_emp::SetAll()
	{
		using std::cout;
		using std::endl;
		using std::cin;

		cout << "Please set the first name.\n";
		cin >> fname;
		cout << "Please set the second name.\n";
		cin >> lname;
		cout << "Please set the job.\n";
		cin >> job;
	}

	std::ostream& operator<<(std::ostream &os, const abstr_emp &e)
	{
		using std::endl;
		os << endl;
		os << e.fname << " " << e.lname << " " << e.job;
		return os;
	}

	void employee::ShowAll() const
	{
		abstr_emp::ShowAll();
	}

	void employee::SetAll()
	{
		abstr_emp::SetAll();
	}

	void manager::ShowAll() const
	{
		using std::cout;
		using std::endl;

		abstr_emp::ShowAll();
		cout << "In charge of: " << inchargeof << endl;
	}

	void manager::SetAll() 
	{
		using std::cin;
		using std::cout;
		using std::endl;

		abstr_emp::SetAll();
		cout << "Please set the in charge of.\n";
		cin >> inchargeof;
	}

	void fink::ShowAll() const
	{
		abstr_emp::ShowAll();
		std::cout << "Reports to: " << reportsto << std::endl;
	}

	void fink::SetAll()
	{
		abstr_emp::SetAll();
		std::cout << "Please set the reports to.\n";
		std::cin >> reportsto;
	}

	void highfink::ShowAll() const
	{
		abstr_emp::ShowAll();
		std::cout << "In charge of: " << InChargeOf() << std::endl;
		std::cout << "Reports to: " << ReportsTo() << std::endl;
	}

	void highfink::SetAll()
	{
		abstr_emp::SetAll();
		std::cout << "Please set the in charge of.\n";
		std::cin >> InChargeOf();
		std::cout << "Please set the reports to.\n";
		std::cin >> ReportsTo();
		
	}

	
}

int main()
{
	using namespace Abstr_emp;
	using namespace std;

	employee em("Trip", "Harris", "Thumper");
	cout << em << endl;
	em.ShowAll();
	manager ma("Anorphia", "Spindragon", "Nuancer", 5);
	cout << ma << endl;
	ma.ShowAll();

	fink fi("Matt", "Oggs", "Oiler", "Juno Barr");
	cout << fi << endl;
	fi.ShowAll();
	highfink hf(ma, "Curly Kew");
	hf.ShowAll();
	cout << "Press a key for next phase:\n";
	cin.get();
	highfink hf2;
	hf2.SetAll();

	cout << "Using an abstr emp * pointer:\n";
	abstr_emp *tri[4] = { &em,&fi,&hf,&hf2 };
	for (int i = 0; i < 4; i++)
		tri[i]->ShowAll();

	system("pause");
	return 0;
	
}