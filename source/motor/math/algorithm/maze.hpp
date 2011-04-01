#ifndef _MAZE_HPP
#define _MAZE_HPP

namespace motor
{
	class Maze
	{
	};
}
#endif


//create a CellStack (LIFO) to hold a list of cell locations  
//set TotalCells = number of cells in grid  
//choose a cell at random and call it CurrentCell  
//set VisitedCells = 1  
//   
//   while VisitedCells < TotalCells 
//   find all neighbors of CurrentCell with all walls intact   
//   if one or more found 
//   choose one at random  
//   knock down the wall between it and CurrentCell  
//   push CurrentCell location on the CellStack  
//   make the new cell CurrentCell  
//   add 1 to VisitedCells
//   else 
//   pop the most recent cell entry off the CellStack  
//   make it CurrentCell
//   endIf
//   endWhile  
