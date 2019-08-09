
#include <iterator>

#include "scarltypes.h"
#include "y.tab.h"

using namespace std;

Type_Descriptor::Type_Descriptor() { }

/** PRIMITIVE TYPES **/

Primitive_Type::Primitive_Type(int primitiveType) {
    if (primitiveType == INT || primitiveType == BOOL || primitiveType == CHAR) {
        this->primitiveType = primitiveType;
    }
    else {
        this->primitiveType = SCARL_INVALID_ARGUMENT; // ERROR
    }
}

Type_Comparison Primitive_Type::compareWith(Type_Descriptor *otherType) {
    if (otherType->getTypeClass() != PRIMITIVE_TYPE) {
        return TYPES_NOT_EQUAL;
    }
    else {
        // the other one is a primitive type
        Primitive_Type *otherPrimitive = dynamic_cast<Primitive_Type*>(otherType);
        if (otherPrimitive->getPrimitiveType() == this->getPrimitiveType()) {
            return TYPES_EQUAL;
        }
        else {
            // all primitives can be converted to each other, roughly
            return TYPES_CONVERTABLE;
        }
    }
}

Type_Class Primitive_Type::getTypeClass() {
    return PRIMITIVE_TYPE;
}

int Primitive_Type::getPrimitiveType() {
    return this->primitiveType;
}

/** END PRIMITIVE TYPES **/

/** POINTER TYPES **/

Pointer_Type::Pointer_Type(Type_Descriptor *pointingTo) {
    if (pointingTo->getTypeClass() != POINTER_TYPE) {
        this->pointingTo = pointingTo;
    }
    else {
        this->pointingTo = nullptr;
    }
}

Pointer_Type::~Pointer_Type() {
    delete pointingTo;
}

Type_Comparison Pointer_Type::compareWith(Type_Descriptor *otherType) {
    // we need to determine the rules for
    // pointers more fully before doing this
    // part

    return TYPES_NOT_EQUAL;
}

Type_Class Pointer_Type::getTypeClass() {
    return POINTER_TYPE;
}

Type_Descriptor *Pointer_Type::getTypePointingTo() {
    return this->pointingTo;
}

/** END POINTER TYPES **/

/** ARRAY TYPES **/

Array_Type::Array_Type(Type_Descriptor *containingType, int length) {
    if (length >= 1) {
        this->containingType = containingType;
        this->length = length;
    }
    else {
        this->length = 0;
        this->containingType = nullptr;
    }
}

Array_Type::~Array_Type() {
    delete containingType;
}

Type_Comparison Array_Type::compareWith(Type_Descriptor *otherType) {
    // arrays are strictly typed in that
    // they are only equal if their lengths and
    // types are the same. They are not equal
    // otherwise
    if (otherType->getTypeClass() != ARRAY_TYPE) {
        return TYPES_NOT_EQUAL;
    }
    else {
        Array_Type *otherArray = dynamic_cast<Array_Type*>(otherType);
        if (otherArray->getLength() == this->getLength() &&
            otherArray->getContainingType()->compareWith(this->getContainingType()) == TYPES_EQUAL
        ) {
            return TYPES_EQUAL;
        }
        else {
            return TYPES_NOT_EQUAL;
        }
    }
}

Type_Class Array_Type::getTypeClass() {
    return ARRAY_TYPE;
}

Type_Descriptor *Array_Type::getContainingType() {
    return this->containingType;
}

int Array_Type::getLength() {
    return this->length;
}

/** END ARRAY TYPES **/

/** FUNCTION TYPES **/

Function_Type::Function_Type(Type_Descriptor *returnType, vector<Type_Descriptor*> formalParameters) {
    this->returnType = returnType;
    this->formalParameters = formalParameters;
}

Function_Type::~Function_Type() {
    delete returnType;
    for (vector<Type_Descriptor*>::iterator itr = formalParameters.begin();
            itr != formalParameters.end(); itr++
    ) {
        Type_Descriptor *typeObj = *itr;
        delete typeObj;
    }
}

Type_Comparison Function_Type::compareWith(Type_Descriptor *otherType) {
    // function types are only equivalent when
    // the return types and formal parameters match,
    // otherwise they are not equal

}

Type_Class Function_Type::getTypeClass() {
    return FUNCTION_TYPE;
}

Type_Descriptor *Function_Type::getReturnType() {
    return returnType;
}

vector<Type_Descriptor*> &Function_Type::getFormalParameters() {
    return formalParameters;
}

/** END FUNCTION TYPES **/


/** CLASS TYPE **/

// singleton that has its class defined farther down
// for storing the class definitions so there only needs to
// be a single instance. This is like a global symbol
// table. Classes are meant to have global scope (in this version)
Class_Type_Table singletonClassTypeTable;

Class_Type::Class_Type(string className) {
    // this type should have already been registered
	this->instance = singletonClassTypeTable.obtainClassTypeInstance(className);
}

Class_Type::~Class_Type() {
    //delete instance;
}

Type_Comparison Class_Type::compareWith(Type_Descriptor *otherType) {
    // Classes are only equal if their methods, fields and
    // functions are equal.
    // They are convertable if the class that is being "comparedWith" is
    // either a parent or a descendent in this type hierarchy.
    // the actual polymorphism can take place at runtime, and the
    // programmer is assumed to know what they are doing (runtime checks?)



    return TYPES_NOT_EQUAL;
}

Type_Class Class_Type::getTypeClass() {
    return CLASS_TYPE;
}

vector<Type_Descriptor*> &Class_Type::getClassFields() {
    return this->instance->getClassFields();
}

vector<Function_Type*> &Class_Type::getClassMethods() {
    return this->instance->getClassMethods();
}

Class_Type Class_Type::getParentClass() {
    return this->instance->getParentClass();
}

string Class_Type::getClassName() {
    return this->instance->getClassName();
}

/** END CLASS TYPES **/

/** INSTRASTRUCTURE FOR POLYMORPHISM AND TYPE CONVERSIONS **/
// CLASS TYPE TABLE

Class_Type_Table_Entry::Class_Type_Table_Entry(string className, vector<Type_Descriptor*> classFields, vector<Function_Type*> classMethods, string parentClass) {
    this->className = className;
    this->classFields = classFields;
    this->classMethods = classMethods;
    this->parentClass = parentClass;
}

Class_Type_Table_Entry::~Class_Type_Table_Entry() {
    // deep delete
    //delete this->parentClass;
    for (vector<Type_Descriptor*>::iterator itr = classFields.begin();
            itr != classFields.end(); itr++
    ) {
        Type_Descriptor *typeObj = *itr;
        delete typeObj;
    }
    for (vector<Function_Type*>::iterator itr = classMethods.begin();
            itr != classMethods.end(); itr++
    ) {
        Function_Type *typeObj = *itr;
        delete typeObj;
    }
}

vector<Type_Descriptor*> &Class_Type_Table_Entry::getClassFields() {
    return this->classFields;
}

vector<Function_Type*> &Class_Type_Table_Entry::getClassMethods() {
    return this->classMethods;
}

string Class_Type_Table_Entry::getClassName() {
    return this->className;
}

Class_Type Class_Type_Table_Entry::getParentClass() {
    return Class_Type(this->parentClass);
}

// TYPE TABLE TO KEEP TRACK OF CLASS TYPES

Class_Type_Table::Class_Type_Table() {
    this->entries = vector<Class_Type_Table_Entry*>();
}

void Class_Type_Table::registerType(string className, vector<Type_Descriptor*> classFields, vector<Function_Type*> classMethods, string parentClass) {
    Class_Type_Table_Entry *newEntry = new Class_Type_Table_Entry(className, classFields, classMethods, parentClass);
    this->entries.push_back(newEntry);
}

Class_Type_Table_Entry *Class_Type_Table::obtainClassTypeInstance(string className) {
	for (vector<Class_Type_Table_Entry*>::iterator itr = this->entries.begin(); itr != this->entries.end(); itr++) {
		if ((*itr)->getClassName() == className) {
			return *itr;
		}
	}
	return nullptr;
}

// O(N) search through all defined classes to construct a list 
vector<Class_Type> Class_Type_Table::getClassChildren(string className) {
	vector<Class_Type> children;
	Class_Type parentClass = Class_Type(className);
	for (vector<Class_Type_Table_Entry*>::iterator itr = this->entries.begin(); itr != this->entries.end(); itr++) {
		// if this class is a direct descendent of the chosen parent
		Class_Type temp((*itr)->getClassName());
		if (isDirectDescendantOf(&temp, &parentClass)) {
			children.push_back(temp);
		}
	}
	return children;
}

// GLOBAL CLASS RELATED FUNCTIONS

/* Is the right hand side a descendent of the left hand side? */
bool isDescendentOf(Class_Type *lhs, Class_Type *rhs) {
    // if the right hand side can be found
    // in the left hand side's children tree

}

/* Is the right hand side a direct descendent (immediate child) of the left hand side? */
bool isDirectDescendantOf(Class_Type *lhs, Class_Type *rhs) {
	
}

/* Is the right hand side an ancestor of the left hand side? */
bool isAncestorOf(Class_Type *lhs, Class_Type *rhs) {
    // if you can find the right hand side
    // while going up the type hierarchy

}
