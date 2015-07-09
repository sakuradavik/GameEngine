#include "pch.h"
#include "Scope.h"

using namespace Library;

#pragma region Scope

RTTI_DEFINITIONS(Scope)

const std::uint32_t Scope::DefaultCapacity = 7;

Scope::Scope(std::uint32_t capacity) :
mTable(capacity), mParent(nullptr), mOrderVector(capacity)
{
}

Scope::Scope(const Scope& rhs) :
mParent(nullptr), mTable(), mOrderVector()
{
	operator=(rhs);
}

Scope& Scope::operator=(const Scope& rhs)
{
	if (this != &rhs)
	{
		Orphan();
		Clear();

		for (std::uint32_t i = 0; i < rhs.mOrderVector.Size(); ++i)
		{
			auto entry = rhs.mOrderVector[i];

			if (entry->second.GetType() == Datum::DatumType::Table)
			{
				for (std::uint32_t j = 0; j < entry->second.Size(); ++j)
				{
					if (entry->second.GetScope(j))
					{
						Scope * s = new Scope();
						*s = *(entry->second.GetScope());
						Adopt(*s, entry->first,j);
					}
				}
			}
			else
			{
				Datum& d = Append(entry->first, entry->second.GetType());
				d = entry->second;
			}
		}
	}
	return *this;
}

Scope::~Scope()
{
	Orphan();
	Clear();
}

Datum* Scope::Find(const std::string& key) const
{
	auto iter = mTable.Find(key);
	Datum* d;

	if (iter != mTable.end())
	{
		d = &iter->second;
	}
	else
	{
		d = nullptr;
	}

	return d;
}

Datum* Scope::Search(const std::string& key, Scope** foundScope) const
{
	Datum* datum = Find(key);

	if (!datum)
	{
		if (mParent)
		{
			datum = mParent->Search(key, foundScope);
			if (foundScope)
			{
				*foundScope = mParent;
			}
		}
		else
		{
			datum = nullptr;
		}
	}
	else
	{
		if (foundScope)
		{
			*foundScope = const_cast<Scope*>(this);
		}
	}

	return datum;
}

Datum& Scope::Append(const std::string& key, const Datum::DatumType datumType)
{
	//TODO: throw exception if type is empty string
	bool inserted;
	auto& iter = *mTable.Insert(key, Datum(), inserted);

	if (iter.second.GetType() == Datum::DatumType::Unknown)
	{
		iter.second.SetType(datumType);
	}

	if (inserted)
	{
		mOrderVector.PushBack(&(iter));
	}

	return iter.second;
}

Scope& Scope::AppendScope(const std::string& key)
{
	Datum* datum = Find(key);
	//TODO: Push Back when removing from Vector
	//Found key, check if type is table
	if (datum)
	{
		if (datum->IsExternal() || (datum->GetType() != Datum::DatumType::Table))
		{
			throw std::exception("This Datum is not of the right type");
		}
		Scope* newScope = new Scope();
		newScope->mParent = this;
		datum->Set(newScope, datum->Size());
		return *datum->GetScope(datum->Size() - 1);
	}
	else
	{
		//key not found
		Datum& d = Append(key, Datum::DatumType::Table);
		Scope* newScope = new Scope();
		newScope->mParent = this;
		d.Set(newScope, 0);
		return *d.GetScope(0);
	}
}

void Scope::Adopt(Scope& childToAdopt, const std::string& key, const std::uint32_t index)
{
	if (childToAdopt.GetParent())
		childToAdopt.Orphan();

	Datum * foundDatum = Find(key);
	if (foundDatum)
	{
		if ((foundDatum->GetType() != Datum::DatumType::Table) || foundDatum->IsExternal())
			throw std::exception("You are trying to adopt into a invalid scope");

		if ((foundDatum->GetType() == Datum::DatumType::Table))
		{
			if (index >= foundDatum->Size())
			{
				foundDatum->Set(&childToAdopt, index);
				foundDatum->GetScope(index)->mParent = this;
			}
			else
			{
				Scope* temp = foundDatum->GetScope(index);
				foundDatum->Set(&childToAdopt, index);
				foundDatum->GetScope(index)->mParent = this;
				for (std::uint32_t i = index + 1; i < foundDatum->Size(); ++i)
				{
					Scope* temp2 = foundDatum->GetScope(i);
					foundDatum->Set(temp, i);
					temp = temp2;
				}
				foundDatum->Set(temp, foundDatum->Size());
			}
		}
	}
	else
	{
		Datum& d = Append(key, Datum::DatumType::Table);
		d.Set(&childToAdopt);
		d.GetScope()->mParent = this;
	}
}

Scope* Scope::GetParent() const
{
	return mParent;
}

bool Scope::operator==(const Scope& rhs) const
{
	if ((rhs.mOrderVector.Size() != mOrderVector.Size()))
	{
		return false;
	}

	auto it = rhs.mOrderVector.begin();
	for (auto it2 = mOrderVector.begin(); it2 != mOrderVector.end(); ++it, ++it2)
	{
		if (((*it)->first != (*it2)->first) && ((*it)->second != (*it2)->second))
		{
			return false;
		}
	}
	return true;
}

bool Scope::operator!=(const Scope& rhs) const
{
	return !operator==(rhs);
}

Datum& Scope::operator[](const std::string& key)
{
	return Append(key);
}

Datum& Scope::operator[](const std::uint32_t index)
{
	if (index >= mOrderVector.Size())
	{
		throw std::exception("Index out of bounds");
	}
	return mOrderVector[index]->second;
}

bool Scope::FindName(const Scope& scope, std::string& foundName) const
{
	for (std::uint32_t i = 0; i < mOrderVector.Size(); ++i)
	{
		auto entry = mOrderVector[i];
		if (entry->second.GetType() == Datum::DatumType::Table)
		{
			for (std::uint32_t j = 0; j < entry->second.Size(); ++j)
			{
				if (entry->second.GetScope(j) == &scope)
				{
					foundName = entry->first;
					return true;
				}
			}
		}
	}
	return false;
}

void Scope::Clear()
{
	for (std::uint32_t i = 0; i < mOrderVector.Size(); ++i)
	{
		if (mOrderVector[i])
		{
			if (mOrderVector[i]->second.GetType() == Datum::DatumType::Table)
			{
				for (std::uint32_t j = 0; j < mOrderVector[i]->second.Size(); ++j)
				{
					auto* scope = mOrderVector[i]->second.GetScope(j);

					if (scope)
					{
						if (!mOrderVector[i]->second.IsExternal())
						{
							delete mOrderVector[i]->second.GetScope(j);
						}
						else
						{
							mOrderVector[i]->second.GetScope(j)->mParent = nullptr;
						}
					}
				}
			}
		}
	}

	mTable.Clear();
	mOrderVector.Clear();
}

void Scope::Orphan()
{
	if (mParent != nullptr)
	{
		std::uint32_t index = 0;
		Datum* datum = mParent->FindNestedScope(this, index);
		if (datum == nullptr)
		{
			throw std::exception("You are not a child of this parent");
		}

		datum->Set(static_cast<Scope*>(nullptr), index);
		mParent = nullptr;
	}

}

Datum* Scope::FindNestedScope(Scope *scopeToFind, std::uint32_t& index) const
{
	// Iterate through the string/Datum pairs looking for DatumType::Table entries
	for (std::uint32_t i = 0; i < mOrderVector.Size(); ++i)
	{
		Datum& entry = mOrderVector[i]->second;
		if (entry.GetType() == Datum::DatumType::Table)
		{
			// Iterate through the child Scope Datum looking for the specic Scope pointer
			for (std::uint32_t j = 0; j < entry.Size(); ++j)
			{
				if (entry.GetScope(j) == scopeToFind)
				{
					index = j;
					return &entry;
				}
			}
		}
	}
	return nullptr;
}

std::uint32_t Scope::Size() const
{
	return mOrderVector.Size();
}

#pragma endregion
