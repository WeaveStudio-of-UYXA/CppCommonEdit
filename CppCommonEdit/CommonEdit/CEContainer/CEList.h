#pragma once
#include <iostream>
#include "../CECore/CECore.h"

//This macro should be provided by CEMacro.h which in CECore.
//In case you use it alone,the definition is given below.
#ifndef publicOperator
    #define publicOperator public
#endif

namespace CE {
    template<typename T> class CEList
    {
    private:
        struct Unit {
            Unit* NextUnit = CE_NULLPTR;
            Unit* BackUnit = CE_NULLPTR;
            T object;
        };
        Unit* FirstUnit;
        long long gIndex = -1;
        Unit* getUnit(long long index) {
            if (index > gIndex || index < (-gIndex-1) || gIndex == -1) {
                throw "List index out of range";
            }
            Unit* CurrentUnit = FirstUnit;
            if (index >= 0) {
                for (int i = 0; i < index; i++) {
                    CurrentUnit = CurrentUnit->NextUnit;
                }
            }
            else {
                for (int i = 0; i > index; i--) {
                    CurrentUnit = CurrentUnit->BackUnit;
                }
            }
            return CurrentUnit;
        }
        bool insertUnit(long long index, T newUnit) {
            if (gIndex == -1) {
                createFirst(newUnit);
                return TRUE;
            }
            Unit* insertBack = getUnit(index);
            Unit* insertNext;
            if (index >= gIndex) {
                insertNext = getUnit(0);
            }
            else {
                insertNext = getUnit(index + 1);
            }
            Unit* NewUnit = new Unit;
            NewUnit->NextUnit = insertNext;
            NewUnit->BackUnit = insertBack;
            NewUnit->object = newUnit;
            insertBack->NextUnit = NewUnit;
            insertNext->BackUnit = NewUnit;
            gIndex++;
            return TRUE;
        }
        bool createFirst(T newUnit) {
            if (gIndex == -1) {
                Unit* First = new Unit;
                First->NextUnit = First;
                First->BackUnit = First;
                First->object = newUnit;
                FirstUnit = First;
                gIndex = 0;
            }
            else {
                throw "Insider Exception:Create first unit while list is not empty.";
            }
            return TRUE;
        }
        bool removeUnit(long long index) {
            Unit* removeBack;
            if (index <= -gIndex - 1) {
                removeBack = getUnit(gIndex);
            }
            else {
                removeBack = getUnit(index - 1);
            }
            Unit* removeNext;
            if (index >= gIndex) {
                removeNext = getUnit(0);
            }
            else {
                removeNext = getUnit(index + 1);
            }
            delete removeBack->NextUnit;
            if (gIndex != 0) {
                removeBack->NextUnit = removeNext;
                removeNext->BackUnit = removeBack;
                if (index == 0) {
                    FirstUnit = removeNext;
                }
                gIndex--;
            }
            else {
                gIndex = -1;
            }
            
            return TRUE;
        }
        bool clearAll() {
            while (gIndex > -1) {
                removeUnit(0);
            }
            return TRUE;
        }
    public:
        CEList(std::initializer_list<T> Init) {
            for (auto i = Init.begin(); i != Init.end(); i++) {
                insertUnit(gIndex, *i);
            }
        }
        CEList() {}
        ~CEList() {
            clearAll();
        }
        T at(long long index) {
            return getUnit(index)->object;
        }
        void remove(long long index) {
            removeUnit(index);
        }
        long long length() {
            return gIndex + 1;
        }
        void insert(long long index, T newT) {
            insertUnit(index, newT);
        }
        void append(T newT) {
            insertUnit(gIndex, newT);
        }
        void clear() {
            clearAll();
        }
#ifdef CE_QT_5
        QString toQString() {
            QString Output = "{";
            if (gIndex >= 0) {
                for (int i = 0; i < gIndex; i++) {
                    Output.append(QString::number(at(i)));
                    Output.append(", ");
                }
                Output.append(QString::number(at(gIndex)));
            }
            Output.append("}");
            return Output;
        }
#endif
    publicOperator:
        
    };
}