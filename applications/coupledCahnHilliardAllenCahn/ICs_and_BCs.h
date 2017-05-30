template <int dim>
double InitialCondition<dim>::value (const Point<dim> &p, const unsigned int component) const
{
	  double scalar_IC = 0;
	  // =====================================================================
	  // ENTER THE INITIAL CONDITIONS HERE FOR SCALAR FIELDS
	  // =====================================================================
	  // Enter the function describing conditions for the fields at point "p".
	  // Use "if" statements to set the initial condition for each variable
	  // according to its variable index.

	  double dx=spanX/((double) subdivisionsX)/std::pow(2.0,refineFactor);
	  double r=0.0;

	  // Initial condition for the concentration field
	  if (index == 0){
		  if (dim == 2){
			  r=p.distance(Point<dim>(spanX/3.0,spanY/3.0));
			  scalar_IC = 0.009+0.5*(0.125)*(1.0-std::tanh((r-spanX/5.0)/(1.0)));
			  r=p.distance(Point<dim>(3.0*spanX/4.0,3.0*spanY/4.0));
			  scalar_IC += 0.5*(0.125)*(1.0-std::tanh((r-spanX/12.0)/(1.0)));
		  }
		  else if (dim == 3) {
			  r=p.distance(Point<dim>(spanX/3.0,spanY/3.0,spanZ/3.0));
			  scalar_IC = 0.009+0.5*(0.125)*(1.0-std::tanh((r-spanX/5.0)/(1.0)));
			  r=p.distance(Point<dim>(3.0*spanX/4.0,3.0*spanY/4.0,3.0*spanZ/4.0));
			  scalar_IC += 0.5*(0.125)*(1.0-std::tanh((r-spanX/12.0)/(1.0)));
		  }

	  }
	  // Initial condition for the structural order parameter field
	  else {
		  if (dim == 2){
			  r=p.distance(Point<dim>(spanX/3.0,spanY/3.0));
			  scalar_IC = 0.5*(1.0-std::tanh((r-spanX/5.0)/(1.0)));
			  r=p.distance(Point<dim>(3.0*spanX/4.0,3.0*spanY/4.0));
			  scalar_IC += 0.5*(1.0-std::tanh((r-spanX/12.0)/(1.0)));
		  }
		  else if (dim == 3){
			  r=p.distance(Point<dim>(spanX/3.0,spanY/3.0,spanZ/3.0));
			  scalar_IC = 0.5*(1.0-std::tanh((r-spanX/5.0)/(1.0)));
			  r=p.distance(Point<dim>(3.0*spanX/4.0,3.0*spanY/4.0,3.0*spanZ/4.0));
			  scalar_IC += 0.5*(1.0-std::tanh((r-spanX/12.0)/(1.0)));
		  }
	  }

	  // =====================================================================
	  return scalar_IC;
}

template <int dim>
void InitialConditionVec<dim>::vector_value (const dealii::Point<dim> &p, dealii::Vector<double> &vector_IC) const
{
	  // =====================================================================
	  // ENTER THE INITIAL CONDITIONS HERE FOR VECTOR FIELDS
	  // =====================================================================
	  // Enter the function describing conditions for the fields at point "p".
	  // Use "if" statements to set the initial condition for each variable
	  // according to its variable index.


	  // =====================================================================
}

template <int dim, int degree>
void customPDE<dim,degree>::setBCs(){
	// =====================================================================
	// ENTER THE BOUNDARY CONDITIONS HERE
	// =====================================================================
	// This function sets the BCs for the problem variables
	// The function "inputBCs" should be called for each component of
	// each variable and should be in numerical order. Four input arguments
	// set the same BC on the entire boundary. Two plus two times the
	// number of dimensions inputs sets separate BCs on each face of the domain.
	// Inputs to "inputBCs":
	// First input: variable number
	// Second input: component number
	// Third input: BC type (options are "ZERO_DERIVATIVE", "DIRICHLET", and "PERIODIC")
	// Fourth input: BC value (ignored unless the BC type is "DIRICHLET")
	// Odd inputs after the third: BC type
	// Even inputs after the third: BC value
	// Face numbering: starts at zero with the minimum of the first direction, one for the maximum of the first direction
	//						two for the minimum of the second direction, etc.

	this->inputBCs(0,0,"ZERO_DERIVATIVE",0);
	this->inputBCs(1,0,"ZERO_DERIVATIVE",0);

}

