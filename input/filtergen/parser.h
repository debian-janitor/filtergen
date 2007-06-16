/* input parser for the filtergen language
 *
 * Copyright (c) 2003-2007 Jamie Wilkinson <jaq@spacepants.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __FILTERGEN_PARSER_H__
#define __FILTERGEN_PARSER_H__

#include <iostream>

/** Parser for the filtergen language */
class FiltergenParser
{
 public:
  /** Create a new parser object.
   * @param source the stream used as input to the parser
   */
  FiltergenParser(std::istream & source);

  /** Check that the source matches the grammar of this parser.
   * @return bool
   */
  bool check();

 private:
  /** The source file stream. */
  std::istream & source;

  /** Unit test class requiring friend access to private attributes. */
  friend class FiltergenParserTest;
};

#endif /* ! __FILTERGEN_PARSER_H__ */
