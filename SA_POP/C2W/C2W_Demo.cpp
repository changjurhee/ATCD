// -*- C++ -*-
// $Id$

//=============================================================================
/**
 * @file  SA_POP_Demo.cpp
 *
 * This file contains the main() function for the SA-POP demo.
 * 11/19/08 Added the ability for multiple goals - dmack
 * 11/25/08 Added the use of the LogGraph Out Adapter for Visual purposes - dmack
 *
 * @author  John S. Kinnebrew <john.s.kinnebrew@vanderbilt.edu>
 * @author  Daniel L.C. Mack  <daniel.l.mack@vanderbilt.edu>
 */
//=============================================================================

#include <iostream>
#include <fstream>
#include "SA_POP_Types.h"
#include "SA_Builder.h"
#include "UserInput.h"
#include "TaskMapFileIn.h"
#include "SANet/SANetFileIn.h"
#include "LogScreenOut.h"
#include "LogGraphOut.h"

#include <vector>

//Commands to run in the thread
unsigned long WINAPI ThirdThread(PVOID pvParam)
{
	system("dot -Tgif cond.dot -o conds.gif");
	//system("conds.gif");
	return 0;
}

//for displaying conditions
void displayConds(SA_POP::Planner *plans, std::vector<SANet::CondID> checks)
{

  std::ofstream cfile;
  cfile.open("Cond.dot");
  //Produce Graph
  std::cout << "Create Digraph" << std::endl;
  cfile << "strict digraph conds {\n";
  for(int node = 0; node< checks.size(); node++)
  {
	  std::cout << "Next Cond" << std::endl;
	 
	  if(plans->get_cond_val(checks[node]) == 1)
	  {
		cfile <<  "\t" << "\"" << plans->get_cond_name(checks[node]) << " " << checks[node] << "\" [shape = box, color = green];\n";
	  }
	  else
	  {
		cfile <<  "\t" << "\"" << plans->get_cond_name(checks[node]) << " " << checks[node] << "\" [shape = box, color = red];\n";
	  }
	  std::cout << "Ready for Next Cond" << std::endl;

  }
  cfile << "}\n";
  
  cfile.close();

  unsigned long dwThreadId;
  // Create a new thread.
  char *imageName = "conds.gif";
  HANDLE tThread = CreateThread(NULL, 0, ThirdThread, (PVOID) imageName,
								0, &dwThreadId);
  CloseHandle(tThread);

}

int main (int argc, char* argv[])
{
  SA_POP::SA_Builder builder;
  SANet::SANetFileIn sanet_in;
  SA_POP::TaskMapFileIn tm_in;
  std::string sanet_filename = "";
  std::string tm_filename = "";
  std::vector<SA_POP::CondID> * kconds = new std::vector<SA_POP::CondID>;
  std::vector<SANet::CondID> toCheck;

  // Get filenames from user.
  std::cout << "Task Network file: ";
//  sanet_filename = "../examples/output1.xml";
//  sanet_filename = "../examples/SPACE.san.xml";
//  sanet_filename = "../examples/test_graph1.san.xml";
  std::cin >> sanet_filename;

  std::cout << "Task Map file: ";
//  tm_filename = "../examples/SPACE.tm.xml";
//  tm_filename = "../examples/test_graph.tm.xml";
  std::cin >> tm_filename;

  SA_POP::Goal goal;
  goal.goal_id = "UserSpecifiedGoal ID";
  goal.name = "User specified goal";
  goal.abs_times.clear ();
  goal.rel_times.clear ();
  goal.goal_conds.clear ();
  goal.start_window = std::make_pair (0, 0);

  // Get goal(s).
  int goal_num = 0;
  std::cout << "Number of goals to find: ";
  std::cin >> goal_num;
  for(int g = 0; g < goal_num; g++)
  {
	  SA_POP::CondID goal_id;
	  SA_POP::Utility goal_util;
	  std::cout << "Goal condition ID: ";
	  std::cin >> goal_id;
	  std::cout << "Goal utility: ";
	  std::cin >> goal_util;
	  goal.goal_conds.insert (std::make_pair (goal_id, goal_util));
  }
  

  try {
    sanet_in.build_net (sanet_filename, &builder);
    tm_in.build_task_map (tm_filename, &builder);
  } catch (std::string e) {
    std::cerr << "ERROR while building task network and task map from files:";
    std::cerr << std::endl;
    std::cerr << e;
  } catch (...) {
    std::cerr << "UNKNOWN ERROR while planning." << std::endl;
  }


  SA_POP::Planner *planner = 0;
  SA_POP::LogGraphOut graph_out	(std::cout, 1);


  try {
    planner = builder.get_planner ();

  //Set any probabilities not listed in the XML
	int knownconds = 0;

	std::cout << "How many conditions do we know? ";
	std::cin >> knownconds;

	for(int k = 0; k < knownconds; k++)
	{
		int cid = 0;
		std::cout << "Enter the Condition ID you know:";
		std::cin >> cid;
		SA_POP::CondID ccid = SA_POP::CondID(cid);
		SANet::Probability newprob = SANet::Probability(1);
		planner->update_cond_val(ccid, 1);
		kconds->push_back(ccid);
	
	}

	int track = 0;
  //Conditions to be potentially displayed 
	std::cout << "How many conditions to track? ";
	std::cin >> track;

	for(int t = 0; t < track; t++)
	{
		int cid = 0;
		std::cout << "Enter the Condition ID to track:";
		std::cin >> cid;
		SA_POP::CondID ccid = SA_POP::CondID(cid);
		toCheck.push_back(ccid);
	
	}

    //Configure the OutAdapters to use
    SA_POP::LogScreenOut screen_out (std::cout);
	
    planner->add_out_adapter (&graph_out);
	//SA_POP::SchemaOut s_out	(std::cout, *kconds);
    //planner->add_out_adapter (&s_out);
	//planner->add_out_adapter (&screen_out);

    planner->plan (100, goal);
  } catch (std::string e) {
    std::cerr << "ERROR while planning:" << std::endl;
    std::cerr << e;
    delete planner;
  } catch (...) {
    std::cerr << "UNKNOWN ERROR while planning." << std::endl;
    delete planner;
  }
  
  bool stop = false;
  while(!stop)
  {
	  
	  std::string step;
	  std::cout << "Would you like to advance to the next time step? (Y or N): ";
	  displayConds(planner, toCheck);
	  std::cin >> step;
	  if(step == "Y" || step == "y")
	  {
		  graph_out.moveStep();
		  planner->plan (100, goal);
	  }
	  else
	  {
		  std::string eff;
		  std::cout << "Would you like to negate an effect, change an external condition, or stop? (E or C or S): ";
		  std::cin >>eff;
		  if(eff == "E" || eff == "e")
		  {
			  SA_POP::TaskID curTask;
			  SA_POP::CondID curEff;
			  std::cout << "Enter the Task ID: ";
			  std::cin >> curTask;
			  std::cout << "Enter the Condition ID: ";
			  std::cin >> curEff;
			  //planner->(curTask, curEff, -1);
			  planner->replan(100);

		  }
		  else if(eff == "C" || eff == "c")
		  {
			  SA_POP::CondID envi;
			  SA_POP::Probability newprob;
			  std::cout << "Enter the Condition ID: ";
			  std::cin >> envi;
			  std::cout << "Enter the Probability: ";
			  std::cin >> newprob;
			  planner->update_cond_val(envi, newprob);
			  planner->replan (100, goal);
		  }
		  else
		  {
			  stop = true;
		  }
	  }
  }

  delete planner;

//****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP
  std::cout << "Enter any character to end program: ";
  char temp_;
  std::cin>>temp_;
//****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP

  return 0;
}



