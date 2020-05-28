#include "idx_file.h"

#include <memory>

namespace ml
{

  idx_file::idx_file( const std::string& fileName ) {

    load( fileName );
  }

  idx_file::~idx_file() {
    delete[] _dimensionSizes;
    delete _data;
  }

  bool idx_file::load( const std::string& fileName ) {

    delete[] _dimensionSizes;
    delete _data;

    std::ifstream stream( fileName );

    if ( !stream.is_open() ) {
      return false;
    }

    ReadMagicNumber( stream );

    uint32_t totalBytes = idxDataByteSizes.at(_dataType);
    for ( uint8_t i = 0; i < _dimensions; i++ ) {
      totalBytes *= _dimensionSizes[i];
    }

    _data = std::malloc( totalBytes );
    stream.read( reinterpret_cast<char*>( _data ), totalBytes );
      
    stream.close();
    return true;
  }

  bool idx_file::print( const std::string& fileName ) {

    std::ofstream stream( fileName, std::ios::binary );

    if ( !stream.is_open() ) {
      return false;
    }

    print( stream );
    stream.close();
    return true;
  }

  void idx_file::print( std::ostream& stream ) {

    char zero = (char) 0;

    stream.write( &zero, 1 );
    stream.write( &zero, 1 );
    stream.write( reinterpret_cast<char*>(&_dataType), 1 );
    stream.write( reinterpret_cast<char*>( &_dimensions ), 1 );

    for ( uint8_t i = 0; i < _dimensions; i++ ) {
      uint32_t val = swapByteOrder(_dimensionSizes[i]);
      stream.write( reinterpret_cast<char*>( &val ), 4 );
    }

    stream.write( reinterpret_cast<char*>( _data ), _dataBytes );
  }

  void* idx_file::data() {
    return _data;
  }

  idxDataType idx_file::type() {
    return _dataType;
  }

  uint8_t idx_file::dimensions() {
    return _dimensions;
  }

  uint32_t idx_file::dimensionSize( int dimension ) {
    return _dimensionSizes[dimension];
  }

  void idx_file::ReadMagicNumber( std::ifstream& stream ) {

    char byte;

    //Clear leading 0's.
    stream.read( &byte, 1 );
    stream.read( &byte, 1 );

    //Get data type.
    stream.read( &byte, 1 );
    _dataType = (idxDataType) byte;

    //Read dimensions.
    stream.read( reinterpret_cast<char*>( &_dimensions ), 1 );

    _dimensionSizes = new uint32_t[_dimensions];
    _dataBytes = idxDataByteSizes.at( _dataType );

    for ( uint8_t dim = 0; dim < _dimensions; dim++ ) {
      stream.read( reinterpret_cast<char*>( _dimensionSizes + dim ), 4 );
      _dimensionSizes[dim] = swapByteOrder( _dimensionSizes[dim] );
      _dataBytes *= _dimensionSizes[dim];
    }
  }

  uint16_t idx_file::swapByteOrder( uint16_t data ) {

    return
      ( ( data << 8 ) & 0xff00 ) |
      ( ( data >> 8 ) & 0x00ff );
  }

  uint32_t idx_file::swapByteOrder( uint32_t data ) {

    return 
      ( ( data << 24 )  & 0xff000000 ) |
      ( ( data << 8 ) & 0x00ff0000 ) |
      ( ( data >> 8 ) & 0x0000ff00 ) |
      ( ( data >> 24 ) & 0x000000ff );
  }

  uint64_t idx_file::swapByteOrder( uint64_t data ) {

    return
      ( ( data << 56 ) & 0xff00000000000000 ) |
      ( ( data << 40 ) & 0x00ff000000000000 ) |
      ( ( data << 24 ) & 0x0000ff0000000000 ) |
      ( ( data << 8 ) & 0x000000ff00000000 ) |
      ( ( data >> 8 ) & 0x00000000ff000000 ) |
      ( ( data >> 24 ) & 0x0000000000ff0000 ) |
      ( ( data >> 40 ) & 0x000000000000ff00 ) |
      ( ( data >> 56 ) & 0x00000000000000ff );
  }
}