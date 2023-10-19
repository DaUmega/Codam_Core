import { IsNumber } from "class-validator";

export class BlockDto {
	@IsNumber()
	readonly userId: number;
	@IsNumber()
	readonly blockId: number;
}