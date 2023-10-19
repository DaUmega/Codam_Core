import { IsNumber } from "class-validator";

export class CreateMatchDto {
	@IsNumber()
	readonly playerOneId: number;

	@IsNumber()
	readonly playerTwoId: number;

	@IsNumber()
	readonly winnerId: number;
}