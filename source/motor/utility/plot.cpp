#include "plot.hpp"

motor::Plot::Plot() : out("data/index.html", fstream::out)
{
	out << 
		"<script language=\"javascript\" type=\"text/javascript\" src=\"jquery.js\"></script>\n"
		"<script language=\"javascript\" type=\"text/javascript\" src=\"jquery.flot.js\"></script>\n"
		"<script language=\"javascript\" type=\"text/javascript\" src=\"jquery.flot.navigate.js\"></script>\n"
		"<script language=\"javascript\" type=\"text/javascript\" src=\"jquery.flot.resize.js\"></script>\n"
		"<div id=\"placeholder\" style=\"width:100%;height:100%\"></div>\n"
		"\n"
		"<script type=\"text/javascript\">\n"
		"$(function () \n"
		"{\n";
}
void motor::Plot::addNode(string descr, bool showPoints, bool fill)
{
	nodes[descr].showPoints = showPoints;
	nodes[descr].fill = fill;
	nodes[descr].stepping = .1f;
	nodes[descr].delta = 0.f;
}

void motor::Plot::setStep(float stepping, string descr)
{
	nodes[descr].stepping = stepping;
}

void motor::Plot::add(float f, string descr)
{
	nodes[descr].delta += nodes[descr].stepping;
	add(glm::vec2(nodes[descr].delta, f), descr);
}

void motor::Plot::add(glm::vec2 v, string descr)
{
	nodes[descr].points.push_back(v);
}

void motor::Plot::close()
{
	map<string, node_t>::iterator mIt;
	list<glm::vec2>::iterator listIter;

	for(mIt = nodes.begin(); mIt != nodes.end(); mIt++)
	{
		out << "var data" << (*mIt).first << " = [];\n";
		list<glm::vec2>::iterator lIt;
		for(lIt = nodes[(*mIt).first].points.begin(); lIt != nodes[(*mIt).first].points.end(); lIt++)
		{
			out << "data" << (*mIt).first << ".push([" << (*lIt).x << ", " << (*lIt).y << "]);\n";
			
			if(xMin > (*lIt).x) xMin = (*lIt).x;
			if(xMax < (*lIt).x) xMax = (*lIt).x;

			if(yMin > (*lIt).y) yMin = (*lIt).y;
			if(yMax < (*lIt).y) yMax = (*lIt).y;
		}
	}

	out <<
		"var options = \n"
		"{\n"
		"	series: { lines: { show: true }, shadowSize: 0 },\n"
		"	xaxis: { zoomRange: [0.001, 1000], panRange: [" << xMin  - 1<< ", " << xMax + 1 << "] },\n"
		"	yaxis: { zoomRange: [0.001, 1000], panRange: [" << yMin  - 1<< ", " << yMax + 1 << "] },\n"
		"	zoom: { interactive: true	},\n"
		"	pan: { interactive: true }\n"
		"};\n";

	out << "$.plot($(\"#placeholder\"), [";
	for(mIt = nodes.begin(); mIt != nodes.end(); mIt++)
	{
		out << "{ " << 
			"data: data" << (*mIt).first << ", lines: { show: true, fill: " << ((*mIt).second.fill ? "true" : "false") << "}, points: { show: " << ((*mIt).second.showPoints ? "true" : "false") << "}" <<
					 "}\n";
	}
	out << "] , options);\n";
	out << "}\n);\n</script>\n";

	out.close();
}

motor::Plot::~Plot()
{
	close();
}
