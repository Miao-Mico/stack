#include "main_cfg.h"

#define MAIN_QUEUE_CFG_ADAPT_VECTOR_EN				0u

#define MAIN_QUEUE_CFG_ADAPT_FORWARD_LIST_EN		1u

#if (MAIN_QUEUE_CFG_ADAPT_VECTOR_EN)

#define MAIN_QUEUE_CONTAINER	VECTOR

#define MAIN_QUEUE_CONTAINER_CONTROL	vector_ctrl

vector_stp queue_container = NULL;

#endif // (MAIN_QUEUE_CFG_ADAPT_VECTOR_EN)

#if (MAIN_QUEUE_CFG_ADAPT_FORWARD_LIST_EN)

#define MAIN_QUEUE_CONTAINER	FORWARD_LIST

#define MAIN_QUEUE_CONTAINER_CONTROL	forward_list_ctrl

forward_list_stp queue_container = NULL;

#endif // (MAIN_QUEUE_CFG_ADAPT_FORWARD_LIST_EN)

void main_queue(void)
{
	queue_stp
		queue = NULL,
		queue_adapt = NULL,
		queue_copy = NULL;

	char
		**string = calloc(1, sizeof(char **)),
		*string_start = "####",
		string_moudle[] = "queue";

	printf("\r\n ------------------------+ queue demo start +------------------------ \r\n");

	printf("queue.init start\r\n");
	queue_ctrl.configuration.init(&queue, MAIN_QUEUE_CONTAINER, sizeof(string_moudle), NULL, NULL);		/* Initialize queue,char[sizeof(string_moudle)] type */
	MAIN_QUEUE_CONTAINER_CONTROL.configuration.init(&queue_container, sizeof(string_moudle), NULL, NULL);		/* Initialize queue_container,char[sizeof(string_moudle)] type */
	queue_ctrl.configuration.adapt(&queue_adapt, queue_container);

	printf("\r\nqueue.max_size start\r\n");
	printf("max size : %d \r\n    ", queue_ctrl.capacity.max_size(queue));

	printf("\r\nqueue_adapt.max_size start\r\n");
	printf("max size : %d \r\n    ", queue_ctrl.capacity.max_size(queue_adapt));

	printf("\r\nqueue.push start\r\n");
	for (size_t cnt = 0; cnt < 10; cnt++) {
		printf("push no.%d : \"%s\" \r\n", cnt, string_moudle);

		queue_ctrl.modifiers.push(queue, string_moudle);

		string_moudle[0] += 1;
	}

	printf("\r\nqueue.front start\r\n");
	printf("front : \"%s\" \r\n", (char *)queue_ctrl.element_access.front(queue));

	printf("\r\nqueue.back start\r\n");
	printf("back : \"%s\" \r\n", (char *)queue_ctrl.element_access.back(queue));

	printf("\r\nqueue & queue_adapt.copy queue start\r\n");
	queue_ctrl.modifiers.copy(&queue_adapt, queue);

	printf("\r\nqueue_adapt.pop start\r\n");
	for (size_t cnt = 0; cnt < 10; cnt++) {
		printf("front no.%d : \"%s\" \r\n", cnt, (char *)queue_ctrl.element_access.front(queue_adapt));
		queue_ctrl.modifiers.pop(queue_adapt);
	}

	printf("\r\nqueue.destroy start\r\n");
	queue_ctrl.configuration.destroy(&queue);

	printf("\r\nqueue_adapt.destroy start\r\n");
	queue_ctrl.configuration.destroy(&queue_adapt);

	printf("\r\n ------------------------+ queue demo end +------------------------\r\n");

	return;
}