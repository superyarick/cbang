/******************************************************************************\

          This file is part of the C! library.  A.K.A the cbang library.

              Copyright (c) 2003-2017, Cauldron Development LLC
                 Copyright (c) 2003-2017, Stanford University
                             All rights reserved.

        The C! library is free software: you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public License
        as published by the Free Software Foundation, either version 2.1 of
        the License, or (at your option) any later version.

        The C! library is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
        Lesser General Public License for more details.

        You should have received a copy of the GNU Lesser General Public
        License along with the C! library.  If not, see
        <http://www.gnu.org/licenses/>.

        In addition, BSD licensing may be granted on a case by case basis
        by written permission from at least one of the copyright holders.
        You may request written permission by emailing the authors.

                For information regarding this software email:
                               Joseph Coffland
                        joseph@cauldrondevelopment.com

\******************************************************************************/

#pragma once

#include "Value.h"

#include <limits>


namespace cb {
  namespace JSON {
    class Number : public Value {
      double value;

    public:
      Number(double value = 0) : value(value) {}

      void setValue(double value) {this->value = value;}
      double getValue() const {return value;}

      operator double () const {return value;}

      // From Value
      ValueType getType() const {return JSON_NUMBER;}
      ValuePtr copy(bool deep = false) const {return new Number(value);}
      double getNumber() const {return getValue();}


      int32_t getS32() const {
        if (value < std::numeric_limits<int32_t>::min() ||
            std::numeric_limits<int32_t>::max() < value)
          CBANG_THROWS("Value " << value << " is not a 32-bit signed integer");

        return (int32_t)value;
      }


      uint32_t getU32() const {
        if (value < 0 || std::numeric_limits<uint32_t>::max() < value)
          CBANG_THROWS("Value " << value
                       << " is not a 32-bit unsigned integer");

        return (uint32_t)value;
      }


      int64_t getS64() const {
        if (value < std::numeric_limits<int64_t>::min() ||
            std::numeric_limits<int64_t>::max() < value)
          CBANG_THROWS("Value " << value << " is not a 64-bit signed integer");

        return value;
      }


      uint64_t getU64() const {
        if (value < 0 || std::numeric_limits<uint64_t>::max() < value)
          CBANG_THROWS("Value " << value
                       << " is not a 64-bit unsigned integer");

        return value;
      }


      void set(double value) {this->value = value;}
      void write(Sink &sink) const {sink.write(value);}
    };
  }
}
