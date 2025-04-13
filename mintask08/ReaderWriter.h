#pragma once
#include "Reader.h"
#include "Writer.h"

class ReaderWriter : virtual public Reader, virtual public Writer, virtual public IO {};
