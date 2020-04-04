#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
struct Paper {
	vector<vector<char>>posipaper;
	vector<vector<char>>negipaper;
};
struct translate {
	string oldstate;
	vector<char>oldsym;
	vector<char>newsym;
	vector<char>dir;
	string newstate;
	int general=0;
};
struct TM {
	vector<string> state;
	vector<char> inputsym;
	vector<char> papersym;
	string firststate;
	char blank='_';
	vector<string> finalstate;
	int papernumber=0;
	vector<translate> TMtrans;
};
TM readTM(ifstream &in)
{
	string buff;
	string singlestate;
	TM tm;
	while (getline(in, buff))
	{
		if (buff[0] == ';')continue;
		if (buff[0] == '#')
		{
			singlestate.clear();
			if (buff[1] == 'Q')
			{
				bool readingmode = false;
				for (int index = 2; index < buff.size(); index++)
				{
					if (buff[index] == '}')
					{
						tm.state.push_back(singlestate);
						singlestate.clear();
						break;
					}if (readingmode == false && buff[index] == '{')
						readingmode = true;
					else if (readingmode == true)
					{
						if (buff[index] != ',')
						{
							singlestate.push_back(buff[index]);
						}
						else//read the dot
						{
							tm.state.push_back(singlestate);
							singlestate.clear();
						}
					}
				}
			}
			else if (buff[1] == 'S')
			{
				bool readingmode = false;
				for (int index = 2; index < buff.size(); index++)
				{
					if (buff[index] == '}')break;
					if (readingmode == false && buff[index] == '{')
						readingmode = true;
					else if (readingmode == true)
					{
						if (buff[index] != ',')
						{
							tm.inputsym.push_back(buff[index]);
						}
					}
				}
			}
			else if (buff[1] == 'G') {
				bool readingmode = false;
				for (int index = 2; index < buff.size(); index++)
				{
					if (buff[index] == '}')break;
					if (readingmode == false && buff[index] == '{')
						readingmode = true;
					else if (readingmode == true)
					{
						if (buff[index] != ',')
						{
							tm.papersym.push_back(buff[index]);
						}
					}
				}
			}
			else if (buff[1] == 'q' && buff[2] == '0')
			{
				for (int index = 3; index < buff.size(); index++)
				{
					if (buff[index] != '=' && buff[index] != ' ')
						singlestate.push_back(buff[index]);
				}
				tm.firststate = singlestate;
				singlestate.clear();
			}
			else if (buff[1] == 'B')
			{
				for (int index = 2; index < buff.size(); index++)
				{
					if (buff[index] != '=' && buff[index] != ' ')
						tm.blank = buff[index];
				}
			}
			else if (buff[1] == 'F')
			{
				{
					bool readingmode = false;
					for (int index = 2; index < buff.size(); index++)
					{
						if (buff[index] == '}')
						{
							tm.finalstate.push_back(singlestate);
							singlestate.clear();
							break;
						}
						if (readingmode == false && buff[index] == '{')
							readingmode = true;
						else if (readingmode == true)
						{
							if (buff[index] != ',')
							{
								singlestate.push_back(buff[index]);
							}
							else//read the dot
							{
								tm.finalstate.push_back(singlestate);
								singlestate.clear();
							}
						}
					}
				}
			}
			else if (buff[1] == 'N') {
				for (int index = 2; index < buff.size(); index++)
				{
					if (buff[index] != '=' && buff[index] != ' ')
						tm.papernumber = buff[index] - '0';
				}
			}
		}
		else if(buff.size())//translate fanction 
			{
			singlestate.clear();
			translate trans; int index = 0;
			for (index = 0; buff[index] != ' '; index++)
			{
				
				singlestate.push_back(buff[index]);
			}
			index++;
			trans.oldstate = singlestate;
			singlestate.clear();
			for (; buff[index] != ' '; index++)
			{
				trans.oldsym.push_back(buff[index]);
				if (buff[index] == '*')
					trans.general++;
			}
			index++;
			for (; buff[index] != ' '; index++)
			{
				trans.newsym.push_back(buff[index]);
				if (buff[index] == '*')
					trans.general++;
			}
			index++;
			for (; buff[index] != ' '; index++)
			{
				trans.dir.push_back(buff[index]);
			}
			index++;
			for (; buff[index] != ' ' && index < buff.size(); index++)
			{
				singlestate.push_back(buff[index]);
			}
			trans.newstate = singlestate;
			singlestate.clear();
			tm.TMtrans.push_back(trans);
			}
	}
	return tm;
}
void printTM(TM &tm) {
	cout << "TM's state:";
	for (int i = 0; i < tm.state.size(); i++)
		cout << tm.state[i] << " ";
	cout << endl;
	cout << "TM's input symbol:";
	for (int i = 0; i < tm.inputsym.size(); i++)
		cout << tm.inputsym[i] << " ";
	cout << endl;
	cout << "TM's paper symbol:";
	for (int i = 0; i < tm.papersym.size(); i++)
		cout << tm.papersym[i] << " ";
	cout << endl;
	cout << "TM's first state:";
	cout << tm.firststate;
	cout << endl;
	cout << "TM's blank:";
	cout << tm.blank;
	cout << endl;
	cout << "TM's final state:";
	for (int i = 0; i < tm.finalstate.size(); i++)
		cout << tm.finalstate[i] << " ";
	cout << endl;
	cout << "TM's papernumber:";
	cout << tm.papernumber;
	cout << endl;
	cout << "TM's translate:";
	for (int i = 0; i < tm.TMtrans.size(); i++)
	{
		cout << tm.TMtrans[i].oldstate << " ";
		for (int j = 0; j < tm.TMtrans[i].oldsym.size(); j++)
		{
			cout << tm.TMtrans[i].oldsym[j];
		}
		cout << " ";
		for (int j = 0; j < tm.TMtrans[i].newsym.size(); j++)
		{
			cout << tm.TMtrans[i].newsym[j];
		}
		cout << " ";
		for (int j = 0; j < tm.TMtrans[i].dir.size(); j++)
		{
			cout << tm.TMtrans[i].dir[j];
		}
		cout << " ";
		cout << tm.TMtrans[i].newstate << endl;
	} 

}
bool checkinput(string& in, TM& tm)
{
	bool inthesym = false;
	for (int i = 0; i < in.size(); i++)
	{
		inthesym = false;
		for (int j = 0; j < tm.inputsym.size(); j++)
		{
			if (in[i] == tm.inputsym[j])
			{
				inthesym = true;
				break;
			}
		}
		if (inthesym == false)
			return false;
	}
	return true;
}
void errorconsule(string& in,ofstream& consule)
{
	cout << "==================== ERR ====================" << endl;
	cout << "The input " << in << " is illegal" << endl;
	cout << "==================== END ====================" << endl;
	consule << "==================== ERR ====================" << endl;
	consule << "The input " << in << " is illegal" << endl;
	consule << "==================== END ====================" << endl;
}
void resultconsule(string& in, ofstream& consule) {
	cout << "Result:" << in << endl;
	cout << "==================== END ====================" << endl;
	consule << "Result:" << in << endl;
	consule << "==================== END ====================" << endl;
}
bool typeequal(vector<char>& in, vector<char>& tmfunc)
{
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i] != tmfunc[i] && tmfunc[i] != '*')
			return false;
	}
	return true;
}
int funcselect(TM& tm,string& oldstate, vector<char>&tape)
{
	vector<bool> aval; int select = -1;
	for (int i = 0; i < tm.TMtrans.size(); i++)
	{
		aval.push_back(true);
	}
	for (int i = 0; i < tm.TMtrans.size(); i++)
	{
		if (tm.TMtrans[i].oldstate != oldstate)
			aval[i] = false;
	}
	for (int i = 0; i < tm.TMtrans.size(); i++)
	{
		if (!typeequal(tape, tm.TMtrans[i].oldsym))
			aval[i] = false;
	}
	for (int i = 0; i < tm.TMtrans.size(); i++)
	{
		if (aval[i] && select == -1)
		{
			select = i;
		}
		else if (aval[i] && tm.TMtrans[i].general < tm.TMtrans[select].general)
		{
			select = i;
		}
	}
	return select;
}
void printexe(TM&tm,int step,string& newstate, Paper& paper, vector<int>& head)
{
	int typestart = 0; int typeend = 0; bool paper_start_in_neg = false, paper_end_in_pos = false;
	cout << "Step\t:" << '\t' << step << endl;
	for (int i = 0; i < head.size(); i++)
	{
		typestart = 0; typeend = 0;
		paper_start_in_neg = false;
		for (int index = paper.negipaper[i].size() - 1; index > 0; index--)
		{
			if (paper.negipaper[i][index] != tm.blank)
			{
				paper_start_in_neg = true;
				typestart = -index;
				break;
			}
		}
		if (!paper_start_in_neg)
		{
			for (int index = 0; index < paper.posipaper[i].size(); index++)
			{
				if (paper.posipaper[i][index] != tm.blank)
				{
					typestart = index;
					break;
				}
			}
		}
		paper_end_in_pos = false;
		for (int index = paper.posipaper[i].size() - 1; index > 0; index--)
		{
			if (paper.posipaper[i][index] != tm.blank)
			{
				paper_end_in_pos = true;
				typeend = index;
				break;
			}
		}
		if (!paper_end_in_pos)
		{
			for (int index = paper.negipaper[i].size() - 1; index > 0; index--)
			{
				if (paper.negipaper[i][index] != tm.blank)
				{
					paper_end_in_pos = true;
					typeend = -index;
					break;
				}
			}
		}
		cout << "Index" << i << "\t:";
		if (typestart < 0 && typeend>0)
		{
			for (int index = typestart; index < 0; index++)
			{
				cout << '\t' << -index;
			}
			for (int index = 0; index <= typeend; index++)
			{
				cout << '\t' << index;
			}
			cout << endl;
		}
		else
		{
			if (typestart >= 0)
			{
				for (int index = typestart; index <= typeend; index++)
					cout << '\t' << index;
			}
			else
			{
				for (int index = typestart; index <= typeend; index++)
					cout << '\t' << -index;
			}
			cout << endl;
		}
		cout << "Tape" << i << "\t:";
		if (typestart < 0 && typeend>0)
		{
			for (int index = typestart; index < 0; index++)
			{
				cout << '\t' << paper.negipaper[i][-index];
			}
			for (int index = 0; index <= typeend; index++)
			{
				cout << '\t' << paper.posipaper[i][index];
			}
			cout << endl;
		}
		else
		{
			if (typestart >= 0)
			{
				for (int index = typestart; index <= typeend; index++)
					cout << '\t' << paper.posipaper[i][index];
			}
			else
			{
				for (int index = typestart; index <= typeend; index++)
					cout << '\t' << paper.negipaper[i][-index];
			}
			cout << endl;
		}
		cout << "Head" << i << "\t:";
		if (typestart < 0 && typeend>0)
		{
			for (int index = typestart; index < 0; index++)
			{
				if (index == head[i])
					cout << '\t' << "^";
				else cout << '\t' << " ";
			}
			for (int index = 0; index <= typeend; index++)
			{
				if (index == head[i])
					cout << '\t' << "^";
				else cout << '\t' << " ";
			}
			cout << endl;
		}
		else
		{
			if (typestart >= 0)
			{
				for (int index = typestart; index <= typeend; index++)
					if (index == head[i])
						cout << '\t' << "^";
					else cout << '\t' << " ";
			}
			else
			{
				for (int index = typestart; index <= typeend; index++)
					if (index == head[i])
						cout << '\t' << "^";
					else cout << '\t' << " ";
			}
			cout << endl;
		}
	}
	cout << "State\t:\t" << newstate << endl;
}
void printconsule(ofstream &out,TM& tm, int step, string& newstate, Paper& paper, vector<int>& head)
{
	int typestart = 0; int typeend = 0; bool paper_start_in_neg = false, paper_end_in_pos = false;
	out << "Step\t:" << '\t' << step << endl;
	for (int i = 0; i < head.size(); i++)
	{
		typestart = 0; typeend = 0;
		paper_start_in_neg = false;
		for (int index = paper.negipaper[i].size() - 1; index > 0; index--)
		{
			if (paper.negipaper[i][index] != tm.blank)
			{
				paper_start_in_neg = true;
				typestart = -index;
				break;
			}
		}
		if (!paper_start_in_neg)
		{
			for (int index = 0; index < paper.posipaper[i].size(); index++)
			{
				if (paper.posipaper[i][index] != tm.blank)
				{
					typestart = index;
					break;
				}
			}
		}
		paper_end_in_pos = false;
		for (int index = paper.posipaper[i].size() - 1; index > 0; index--)
		{
			if (paper.posipaper[i][index] != tm.blank)
			{
				paper_end_in_pos = true;
				typeend = index;
				break;
			}
		}
		if (!paper_end_in_pos)
		{
			for (int index = paper.negipaper[i].size() - 1; index > 0; index--)
			{
				if (paper.negipaper[i][index] != tm.blank)
				{
					paper_end_in_pos = true;
					typeend = -index;
					break;
				}
			}
		}
		out << "Index" << i << "\t:";
		if (typestart < 0 && typeend>0)
		{
			for (int index = typestart; index < 0; index++)
			{
				out << '\t' << -index;
			}
			for (int index = 0; index <= typeend; index++)
			{
				out << '\t' << index;
			}
			out << endl;
		}
		else
		{
			if (typestart >= 0)
			{
				for (int index = typestart; index <= typeend; index++)
					out << '\t' << index;
			}
			else
			{
				for (int index = typestart; index <= typeend; index++)
					out << '\t' << -index;
			}
			out << endl;
		}
		out << "Tape" << i << "\t:";
		if (typestart < 0 && typeend>0)
		{
			for (int index = typestart; index < 0; index++)
			{
				out << '\t' << paper.negipaper[i][-index];
			}
			for (int index = 0; index <= typeend; index++)
			{
				out << '\t' << paper.posipaper[i][index];
			}
			out << endl;
		}
		else
		{
			if (typestart >= 0)
			{
				for (int index = typestart; index <= typeend; index++)
					out << '\t' << paper.posipaper[i][index];
			}
			else
			{
				for (int index = typestart; index <= typeend; index++)
					out << '\t' << paper.negipaper[i][-index];
			}
			out << endl;
		}
		out << "Head" << i << "\t:";
		if (typestart < 0 && typeend>0)
		{
			for (int index = typestart; index < 0; index++)
			{
				if (index == head[i])
					out << '\t' << "^";
				else out << '\t' << " ";
			}
			for (int index = 0; index <= typeend; index++)
			{
				if (index == head[i])
					out << '\t' << "^";
				else out << '\t' << " ";
			}
			out << endl;
		}
		else
		{
			if (typestart >= 0)
			{
				for (int index = typestart; index <= typeend; index++)
					if (index == head[i])
						out << '\t' << "^";
					else out << '\t' << " ";
			}
			else
			{
				for (int index = typestart; index <= typeend; index++)
					if (index == head[i])
						out << '\t' << "^";
					else out << '\t' << " ";
			}
			out << endl;
		}
	}
	out << "State\t:\t" << newstate << endl;
}
string execute(string in,TM &tm,ofstream& consule)
{
	if (!checkinput(in, tm))
	{
		errorconsule(in,consule);
		return "Error";
	}
	else
	{
		Paper paper;//the setup of paper
		vector<char> mainpaper,negimainpaper;
		int step = 0; vector<int>head; string curstate = tm.firststate;
		for (int i = 0; i < in.size(); i++)
		{
			mainpaper.push_back(in[i]);
		}
		paper.posipaper.push_back(mainpaper);
		negimainpaper.push_back(tm.blank);
		paper.negipaper.push_back(negimainpaper);
		for (int i = 1; i < tm.papernumber; i++)
		{
			vector<char> otherpaper,negiotherpaper;
			otherpaper.push_back(tm.blank);
			negiotherpaper.push_back(tm.blank);
			paper.posipaper.push_back(otherpaper);
			paper.negipaper.push_back(negiotherpaper);
		}
		for (int i = 0; i < tm.papernumber; i++)
		{
			head.push_back(0);
		}
		int select = -1;
		vector<char>tape;
		for (int i = 0; i < tm.papernumber; i++)
		{
			if (head[i] >= 0)
			{
				tape.push_back(paper.posipaper[i][head[i]]);
			}
			else
			{
				tape.push_back(paper.negipaper[i][-head[i]]);
			}
		}
		select = funcselect(tm, curstate, tape);
		tape.clear();
		while (select != -1)
		{
			//select has been found; executed

			step++;
			curstate = tm.TMtrans[select].newstate;
			for (int i = 0; i < tm.papernumber; i++)
			{
				if (head[i] >= 0)
				{
					if (tm.TMtrans[select].newsym[i] == '*');
					else
					paper.posipaper[i][head[i]] = tm.TMtrans[select].newsym[i];
				}
				else
				{
					if (tm.TMtrans[select].newsym[i] == '*');
					else
					paper.negipaper[i][-head[i]] = tm.TMtrans[select].newsym[i];
				}
				if (tm.TMtrans[select].dir[i] == 'r')
				{
					head[i]++;
					if (head[i] >= 0 && head[i] >= paper.posipaper[i].size())
						paper.posipaper[i].push_back(tm.blank);
				}
				else if (tm.TMtrans[select].dir[i] == 'l')
				{
					head[i]--;
					if (head[i] < 0 && (-head[i]) >= paper.negipaper[i].size())
					{
						paper.negipaper[i].push_back(tm.blank);
					}
				}
				//head[i] has been changed
			}
			for (int i = 0; i < tm.papernumber; i++)
			{
				if (head[i] >= 0)
				{
					tape.push_back(paper.posipaper[i][head[i]]);
				}
				else
				{
					tape.push_back(paper.negipaper[i][-head[i]]);
				}
			}
			printconsule(consule, tm, step, curstate, paper, head);
			printexe(tm, step, curstate, paper, head);
			select = funcselect(tm, curstate, tape);
			tape.clear();
		}
		//after select
		bool paper_start_in_neg = false, paper_end_in_pos = false; int typestart = 0, typeend = 0;
		for (int index = paper.negipaper[0].size()-1; index > 0; index--)
		{
			if (paper.negipaper[0][index] != tm.blank)
			{
				paper_start_in_neg = true;
				typestart = -index;
				break;
			}
		}
		if (!paper_start_in_neg)
		{
			for (int index = 0; index < paper.posipaper[0].size()-1; index++)
			{
				if (paper.posipaper[0][index] != tm.blank)
				{
					typestart = index;
					break;
				}
			}
		}
		paper_end_in_pos = false;
		for (int index = paper.posipaper[0].size()-1; index > 0; index--)
		{
			if (paper.posipaper[0][index] != tm.blank)
			{
				paper_end_in_pos = true;
				typeend = index;
				break;
			}
		}
		if (!paper_end_in_pos)
		{
			for (int index = paper.negipaper[0].size()-1; index > 0; index--)
			{
				if (paper.negipaper[0][index] != tm.blank)
				{
					paper_end_in_pos = true;
					typeend = -index;
					break;
				}
			}
		}
		string result;
		if (typestart < 0 && typeend>0)
		{
			for (int index= typestart; index < 0; index++)
			{
				result.push_back(paper.negipaper[0][-index]);
			}
			for (int index = 0; index <= typeend; index++)
			{
				result.push_back(paper.posipaper[0][index]);
			}
		}
		else
		{
			if (typestart >= 0)
			{
				for (int index = typestart; index <= typeend; index++)
					result.push_back(paper.posipaper[0][index]);
			}
			else
			{
				for (int index = typestart; index <= typeend; index++)
					result.push_back(paper.negipaper[0][-index]);
			}
		}
		resultconsule(result, consule);
		return result;
	}
}

int main(int argc,char** argv)
{
	ifstream in;
	string diraddress(argv[1]);
	ofstream consule, result;
	consule.open(diraddress+"/console.txt");
	result.open(diraddress+"/result.txt");
	in.open(diraddress+"/test.tm");
	TM tm = readTM(in);
	in.close();
	printTM(tm);
	in.open(diraddress+"/input.txt");
	string inputbuff;
	string retstring;
	while (getline(in, inputbuff))
	{
		retstring=execute(inputbuff,tm,consule);
		result << retstring << endl;
	}
	result.close();
	consule.close();
	return 0;
}
