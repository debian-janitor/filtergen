/* filtergen
 *
 * Copyright (c) 2003-2010 Jamie Wilkinson <jaq@spacepants.org>
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

#include "driver.h"
#include "parser.hh"

ipts_driver::ipts_driver()
    : trace_scanning(false), trace_parsing(false)
{
}

ipts_driver::~ipts_driver()
{
}

void
ipts_driver::parse(FILE * f, const std::string & fn)
{
    file = f;
    filename = fn;
    scan_begin();
    yy::ipts_parser parser(*this);
    parser.set_debug_level(trace_parsing);
    parser.parse();
    scan_end();
}

void
ipts_driver::error(const yy::location & l,
			const std::string & m)
{
    std::cerr << l << ": " << m << std::endl;
}

void
ipts_driver::error(const std::string & m)
{
    std::cerr << m << std::endl;
}
