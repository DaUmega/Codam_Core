import {
  IsArray,
  IsBoolean,
  IsNotEmpty,
  IsNumber,
  IsOptional,
  IsString,
} from 'class-validator'

class ChannelDto {

  @IsString()
  @IsNotEmpty()
  name: string

  @IsString()
  password: string

  @IsBoolean()
  private: boolean

  @IsNumber()
  ownerId: number
}

export default ChannelDto
