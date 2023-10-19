import { IsBoolean, IsNotEmpty, IsNumber, IsOptional, IsString, Matches, MaxLength, MinLength } from 'class-validator'
/*
use question mark to make the property optional.
*/
export class UpdateUserDto {
	@IsString()
	@IsNotEmpty()
	@IsOptional()
	@MinLength(1)
	@MaxLength(20)
	@Matches(/^[A-Za-z0-9][A-Za-z0-9 ]*[A-Za-z0-9]$/) // only allow digit and alphabet letters, with space in between (not first/last)
	readonly nickname: string; 
	@IsString()
	@IsOptional()
	readonly avatar: string;
	@IsNumber()
	@IsOptional()
	readonly currentStatus: number;
	@IsBoolean()
	@IsOptional()
	readonly twoFacAuth: boolean;
}