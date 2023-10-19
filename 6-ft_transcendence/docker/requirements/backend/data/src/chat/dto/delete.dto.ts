import { IsNotEmpty } from "class-validator";

export class DeleteUserDto {
  @IsNotEmpty()
  adminId!: number;

  @IsNotEmpty()
  deleteId!: number;
}
