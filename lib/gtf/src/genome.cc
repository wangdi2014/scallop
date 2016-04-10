#include <cstdio>
#include <cassert>
#include <sstream>
#include <map>

#include "genome.h"

genome::genome()
{}

genome::genome(const string &file)
{
	read(file);
	sort();
	build_index();
}

genome::~genome()
{
}

int genome::add_gene(const gene &g)
{
	genes.push_back(g);
	return 0;
}

int genome::read(const string &file)
{
	ifstream fin(file.c_str());
	if(fin.fail())
	{
		printf("open file %s error\n", file.c_str());
		return 0;
	}

	char line[102400];
	
	genes.clear();
	vector< vector<exon> > vv;
	map<string, int> m;
	while(fin.getline(line, 102400, '\n'))
	{
		exon ge(line);
		if(ge.feature != "exon") continue;
		if(m.find(ge.gene_id) == m.end())
		{
			vector<exon> v;
			v.push_back(ge);
			vv.push_back(v);
			m.insert(pair<string, int>(ge.gene_id, vv.size() - 1));
		}
		else
		{
			vv[m[ge.gene_id]].push_back(ge);
		}
	}

	for(int i = 0; i < vv.size(); i++)
	{
		gene gg;
		gg.build(vv[i]);
		genes.push_back(gg);
	}

	return 0;
}

int genome::write(const string &file) const
{
	ofstream fout(file.c_str());
	for(int i = 0; i < genes.size(); i++)
	{
		genes[i].write(fout);
	}
	fout.close();
	return 0;
}

int genome::build_index()
{
	s2i.clear();
	for(int i = 0; i < genes.size(); i++)
	{
		s2i.insert(pair<string, int>(genes[i].get_gene_id(), i));
	}
	return 0;
}

int genome::sort()
{
	for(int i = 0; i < genes.size(); i++)
	{
		genes[i].sort();
	}
	return 0;
}

const gene* genome::get_gene(string name) const
{
	map<string, int>::const_iterator it = s2i.find(name);
	if(it == s2i.end()) return NULL;
	int k = it->second;
	return &(genes[k]);
}
