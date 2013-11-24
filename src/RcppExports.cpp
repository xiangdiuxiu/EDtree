// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393
#include "RcppExports.h"

RcppExport SEXP edtree_rcpp_hello_world() {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        List __result = rcpp_hello_world();
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}

int get_nodes(SEXP node)
{
  return 0;
}

void ED_Node(SEXP nodes, SEXP learnsample, SEXP weights, SEXP controls, int isTerminal, int depth)
{
}

void set_nodeID(SEXP node, int nodeID)
{
  //This function will be called by ED_node.
}

void ED_splitnode(SEXP node, SEXP learnsample, SEXP controls, SEXP distance)
{
  //This function will be called by ED_node.
}

bool check_depth(SEXP node, int depth)
{
  //This function will be called by get_nodeterminal
  return false;
}

bool check_nodes(SEXP node, int nodes)
{
  //This function will be called by get_nodeterminal
  return false;
}

bool get_nodeterminal(SEXP node, SEXP controls)
{
  return false;
}

SEXP get_leftnode(SEXP node)
{
  SEXP ans;
  return ans;
}

SEXP get_rightnode(SEXP node)
{
  SEXP ans;
  return ans;
}

void init_node(SEXP node, SEXP learnsample, SEXP weights, SEXP where)
{
  /*
    The key class of this package may be the node class. In fact it is a List.
   */
  Rcpp::List ans = Rcpp::List::create(
				      Rcpp::Named("nodeID"),
				      Rcpp::Named("n_nodes"),
				      Rcpp::Named("weights"),
				      Rcpp::Named("criterion"),
				      Rcpp::Named("split"),
				      Rcpp::Named("isTerminal")
				      );
  ans["nodeID"] = 0; // init value
  ans["n_nodes"] = get_nodes(learnsample); // the number of samples in this node
  ans["weights"] = Rcpp::as<Rcpp::NumericVector>(weights); // weight for different sample
  ans["criterion"] = Rcpp::List::create(); // a null list
  ans["split"] = Rcpp::List::create(); // record the split point and the variable
  ans["isTerminal"] = false;
  node = Rcpp::wrap(ans);
  /*
    We create a list and at last turn it back to an SEXP object. This is not a wise choise.
    But what I want is some kind of unity, as we can use the same formal parameter.
    If the performance is required, we will adapt the function in later version.
    I mean whoever unfortunate will do this job -- not me.
   */

}

void grow_tree(SEXP node, SEXP learnsample, SEXP weights, SEXP where, SEXP distance, SEXP controls, int *nodenum, int depth)
{
  int n_nodes;
  double *dweights; // This is related with the vector where 
  bool stop;

  stop = get_nodeterminal(node, controls);
  if(stop)
    {
      ED_Node(node, learnsample, weights, controls, 1, depth);
    }
  else
    {
      ED_Node(node, learnsample, weights, controls, 0, depth);
    }

  //split and recursion
  if(!stop)
    {
      ED_splitnode(node, learnsample, controls, distance);
      //surrogate split and missing value
      //TODO
      //recursion
      nodenum[0] += 1;
      grow_tree(get_leftnode(node), learnsample, weights, where, distance, controls, nodenum, depth+1);
      nodenum[0] += 1;
      grow_tree(get_leftnode(node), learnsample, weights, where, distance, controls, nodenum, depth+1);
    }
  else
    {
      //deal with dweights
      //TODO
    }
}

/*
  learnsample : at first I want to design a new class for learnsample. But I 
  can't use a self-defined object with Rcpp. As a result learnsample will be a
  List contain data.frame and other type of data.
 */

RcppExport SEXP EDtree_Grow(SEXP learnSample, SEXP weights, SEXP where, SEXP distance, SEXP controls)
{
  SEXP ans;
  //init node
  //It need more work to do before init the node. 
  init_node(ans, learnSample, weights, where);
  //grow tree
  int nodenum = 0;
  grow_tree(ans, learnSample, weights, where, distance, controls, &nodenum, 0);
  return(wrap(ans));
}
