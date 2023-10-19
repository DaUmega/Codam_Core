import { IsNotEmpty } from "class-validator";

export class AddUserDto {
  @IsNotEmpty()
  user!: number;

  password?: string;
}
