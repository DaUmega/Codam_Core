import { IsNumber } from "class-validator";

export class FriendDto {
	@IsNumber()
	readonly userId: number;
	@IsNumber()
	readonly friendId: number;
	@IsNumber()
	readonly action: EditFriendActionType;
}

export enum EditFriendActionType {
	ADD_FRIEND,
	REMOVE_FRIEND,
	SEND_FRIEND_REQUEST,
	REJECT_FRIEND_REQUEST,
}