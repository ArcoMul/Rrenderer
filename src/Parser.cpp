#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#include "Renderer.h"
#include "Context.h"
#include "Parser.h"
#include "Triangle.h"
#include "Mesh.h"

Parser::Parser()
{
}

Mesh Parser::parse(std::string file)
{
	std::vector<std::array<float, 3>> vertexes;
	std::vector<int> faces;
	std::string line;
	std::ifstream myfile(file);
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			if (line[0] == 'v')
			{
				std::string v, x, y, z;
				std::istringstream iss(line);
				iss >> v >> x >> z >> y;
				std::array<float, 3> vertex = { ::atof(x.c_str()), ::atof(y.c_str()), ::atof(z.c_str()) };
				vertexes.push_back(vertex);
			}
			if (line[0] == 'f')
			{
				std::string v, f1, f2, f3;
				std::istringstream iss(line);
				iss >> v >> f1 >> f2 >> f3;
				faces.push_back(std::stoi(f1));
				faces.push_back(std::stoi(f2));
				faces.push_back(std::stoi(f3));
			}
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	Mesh mesh = Mesh();

	for (int i = 0; i < faces.size(); i += 3)
	{
		mesh.addTriangle(Triangle(
			vertexes[faces[i] - 1].data(),
			vertexes[faces[i + 1] - 1].data(),
			vertexes[faces[i + 2] - 1].data()));
	}

	return mesh;
}

Parser::~Parser()
{
}
