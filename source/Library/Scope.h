#pragma once
#include "HashMap.h"
#include "Datum.h"
#include "RTTI.H"

namespace Library
{
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI)

	public:
		typedef std::pair<std::string, Datum> PairType;

		/**
		* Constructor that takes an optional unsigned integer.
		*/
		explicit Scope(std::uint32_t capacity = DefaultCapacity);

		/**
		* Deconstructor.
		*/
		virtual ~Scope();

		/**
		* Copy Constructor.
		*/
		Scope(const Scope& rhs);

		/**
		* Assignment Operator Overload.
		*/
		Scope& operator=(const Scope& rhs);

		/**
		* @brief Takes a constant string and returns the address of a Datum.
		* If it exists, and nullptr
		* @param Takes a constant string
		* @return Returns the adress of the Datum assocaited with the given name
		*/
		Datum* Find(const std::string& key) const;

		/**
		* @brief Takes a constant string and the address of a Scope double pointer. It returns the address of
		* the most-closely nested Datum associated with the given name in this Scope or its ancestors
		* @param constant string and Adress of a Scope double pointer variable
		* @return Returns the adress of a Datum
		*/
		Datum* Search(const std::string& key, Scope** foundScope = nullptr) const;

		/**
		* @brief Takes a constant string and returns a reference to a Datum
		* If it already exists, return that one, otherwise creates a new one
		* If the datum is external or not a table it will throw an error
		* @param a constant string key
		* @return a reference to a Datum
		*/
		Datum& Append(const std::string& key, const Datum::DatumType datumType = Datum::DatumType::Unknown);

		/**
		* @brief Takes a constant string and returns a reference to Scope. It it already exist, returns that
		* that one, else creates a new one.
		* @param const string key
		* @return A reference to a Scope
		*/
		Scope& AppendScope(const std::string& key);

		/**
		* @brief Takes a reference to a Scope, a string and an int and replaces the given child into this
		* table. Will throw an exception if it is external or not of type Table
		* @param A Scope, the child to adopt, a string, the name of the child, and index into the value array
		* @return none
		*/
		void Adopt(Scope& childToAdopt, const std::string& key, const std::uint32_t index = UINT32_MAX);

		/**
		* @brief Returns the address of the Scope which contains this one
		* @param none
		* @return Address to parent
		*/
		Scope* GetParent() const;

		/**
		* @brief Takes a reference to a Scope  and returns a bool indicating if the
		* passed in reference matches this one
		* @param const reference to a Scope
		* @return Bool indicating if the two Scopes are the same
		*/
		bool operator==(const Scope& rhs) const;

		/**
		* @brief Takes a reference to a Scope  and returns a bool indicating if the
		* passed in reference doesn't match this one
		* @param const reference to a Scope
		* @return Bool indicating if the two Scopes are not the same
		*/
		bool operator!=(const Scope& rhs) const;

		/**
		* @brief  Takes a constant string returns a reference Datum
		* @param constant string
		* @return reference to a Datum
		*/

		Datum& operator[](const std::string& value);

		/**
		* @brief  Takes a unsign returns a reference Datum. Will throw an exception if index is greater
		* than the mOrderVector's size
		* @param constant string
		* @return reference to a Datum
		*/
		Datum& operator[](const std::uint32_t index);

		/**
		* @brief Takes a constant address of a Scope and returns the corresponding key
		* @param const Scope address
		* @return key vale of this scope
		*/
		bool FindName(const Scope& scope, std::string& foundName) const;

		/**
		* @brief Will iterate through the scope and calls clears on any of its scope's
		* childrens
		* @param none
		* @return void
		*/
		virtual void Clear();

		/**
		* @brief Will make this scope orphaned from its parent. If the parent does not contain
		* this scope as a child will throw an exception
		* @param none
		* @return void
		*/
		void Orphan();

		std::uint32_t Size() const;

		static const std::uint32_t DefaultCapacity;
		Scope * mParent;

	private:
		Datum* FindNestedScope(Scope *scopeToFind, std::uint32_t& index) const;

		HashMap<std::string, Datum> mTable;
		

	protected:
		Vector<PairType*> mOrderVector;
		

	};
}
