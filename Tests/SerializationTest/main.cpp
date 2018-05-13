#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file


#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/StructWithSimpleTypes.h"
auto pullInLibrary = sw::LinkPrimitivesRegistration();

#include "swCommonLib/External/Catch/catch.hpp"

