/**
 * File: chain.cpp
 * Description: student implementation for Chain functions
 *              for CPSC 221 2023W1 PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
**/

#include <math.h>

#include "chain.h"

/**
 * Constructs a Chain from an input image
 * Each Node will cover a nodedimension x nodedimension (in pixels)
 * region in the source image.
 * @param img the input image
 * @param nodedimension number of pixels along the width and height of the Block region
 * @pre input image's width and height are evenly divisible by nodedimension
**/
Chain::Chain(PNG& img, unsigned int nodedimension) {
	
	length_ = (img.width()  * img.height())/(nodedimension * nodedimension);

	if(length_ != 0 ) {
		NW =  new Node();
		SE = NW;
	for(unsigned int i = 0; i < length_; i++) {
		Node *temp = new Node();
		temp->next = NW;
		temp->next->prev = temp;
		NW = temp;
	}


	}


	Node* temp = NW;
	for(unsigned int i = 0; i < img.width(); i+= nodedimension) {
		for(unsigned int j = 0; j < img.height(); j += nodedimension) {
			Block b;
			temp->data.Build(img, i, j, nodedimension);	
			temp = temp->next;

		}
	}




}

/**
 * Renders the Chain's pixel data into an output PNG.
 * The PNG should be sized according to the number of nodes
 * specified by the cols parameter.
 * It is possible that there may not be enough nodes to fill
 * the bottom row of the PNG. If this happens, just render
 * as many nodes as there are, from left to right, and leave
 * the rest of the row as opaque white pixels.
 * @pre this Chain is not empty
 * @param cols the number of Blocks to use for the width of the image
 * @param full whether to render all pixel data into a full-size image,
 *             or block averages into a tiny image
**/
//KIA
PNG Chain::Render(unsigned int cols, bool full) {
	// replace the line below with your implementation
	// Node *temp = NW;
	// int s = (temp->data).Dimension();

	// PNG* imgFrame = PNG(length_ * s); 
	// int row_limit = 0;

	// if(length_ % cols != 0) {
	// 	row_limit = length_ + 1;
	// }

	// for(int row = 0; row < row_limit; row++) {
	// 	for(int x = 0; x < cols; x++) {

	// 		if(temp) {
	// 		Render(imgFrame, s*x,row*s,full);
	// 		//img_frame._copy(temp->data);
	// 		//temp = temp->next;
	// 		} else {
	// 			Render(imgFrame,s*x,row*s, full);
	// 		}
	
	// 	}
	// }





	/*
	PNG ret();
	Node *temp = NW;
	if (full) {

	} else {

	}
	
	
	*/
	

	// return imgFrame; 
	//return ret;
	return PNG();
}


/**
 * Inserts a new Node containing ndata at the back of the Chain
**/
//KIA
void Chain::InsertBack(const Block& ndata) {

	Node* newNode = new Node(ndata);
	SE->next = newNode;
	SE->next->prev = SE;
	length_ += 1;

    
}

/**
 * Reverses the structure of the list. This must be done by
 * pointer assignments. You may not deallocate or allocate any Nodes.
 * Example:
 *	before:	NW -> A <-> B <-> C <-> D <-> E <-> F <-> G <-> H <- SE
 *  
 *  after:	NW -> H <-> G <-> F <-> E <-> D <-> C <-> B <-> A <- SE
**/
//ALI
void Chain::Reverse() {
	// complete your implementation below
	Node* head = NW->next;
	Node* tail = SE->prev;
	do {
		Node* temp = head;
		head->next = tail->next;
		head->prev = tail->prev;
		tail->next = temp->next;
		tail->prev = temp->prev;
		head = head->next;
		tail = tail->prev;
	}while (head != tail && head->next != tail && tail->prev != head);

    Node* temp = head;
	head = tail;
	tail = temp;
}

/**
 * Rearranges the Node structure and internal pixel data to be flipped over a vertical axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *  before, flipping with 3 columns (2 rows):
 *
 *		NW -> A> <-> B> <-> C> <->
 *            D> <-> E> <-> F> <- SE
 * 
 *  after, visualized with 3 columns (2 rows):
 * 
 *		NW -> <C <-> <B <-> <A <->
 *            <F <-> <E <-> <D <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
**/
//ALI
void Chain::FlipHorizontal(unsigned int cols) {
	// complete your implementation below
	Node* temp = NW;
	Node* temp2 = temp;
	Node* placeHolder = temp;
	while (placeHolder != SE) {
		for (unsigned int i = 0; i < cols; i++) {
			temp2 = temp2->next;
		}
		placeHolder = temp2;
		do {
			Node* temp3 = temp;
			temp->next = temp2->next;
			temp->prev = temp2->prev;
			temp2->next = temp3->next;
			temp2->prev = temp3->prev;

			temp = temp->next;
			temp2 = temp2->prev;
		}while (temp2 != temp && temp->next != temp2 && temp2->prev != temp);

	}
}

/**
 * Rearranges the Node structure and internal pixel data to be flipped over a horizontal axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *	before, flipping with 3 columns (2 rows):
 *                         
 *      NW -> A <-> B <-> C <->
 *            D <-> E <-> F <- SE
 * 
 *  after, visualized with 3 columns (2 rows):
 * 
 *      NW -> D <-> E <-> F <->
 *            A <-> B <-> C <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
**/
//ALI
void Chain::FlipVertical(unsigned int cols) {
	// complete your implementation below
	Node* temp = NW;
	Node* temp2 = SE;
	bool cont = true;
	while (cont) {
		Node* temp3 = temp;
			temp->next = temp2->next;
			temp->prev = temp2->prev;
			temp2->next = temp3->next;
			temp2->prev = temp3->prev;

			temp = temp->next;
			temp2 = temp2->prev;
		for (unsigned int i = 1; i < cols; i++) {
			temp2 = temp2->prev;
		}
		Node* temp4 = temp2;
		for (unsigned int i = 0; i < cols; i++) {
			temp4 = temp4->prev;
			temp = temp->next;
		}
		if (temp4 == temp || temp2 == temp) {
			cont = false;
		}

	}
}

/**
 * Produces a blocky, pixellated effect (in a rendered image) by replacing each
 * block's pixel data with the average color of the block.
**/
//KIA
void Chain::Blockify() {
	Node* temp = NW;
	while(temp != NULL) {
		temp->data.FillAverage();
		temp = temp->next;
	}



}

/**
 * Destroys all dynamically allocated memory associated with
 * this Chain object. Called by destructor and operator=.
 * You must complete its implementation for PA1.
**/
//KIA
void Chain::Clear() {

	Node *temp = NW;

	while(NW != NULL) {
		temp = temp->next;
		delete NW;
		NW = temp;
	}
	NW = NULL;
	SE = NULL;
    
}

/**
 * Copies the parameter other Chain into the current Chain.
 * Does not free any memory. Called by copy constructor and
 * operator=.
 * You must complete its implementation for PA1.
 * @param other The Chain to be copied.
**/
//
void Chain::Copy(const Chain& other) {
	// complete your implementation below
    length_ = other.length_;
	Node* temp = NW;
	while (temp->next){
		Node* temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
	NW->data = other.NW->data;
	NW->next = other.NW->next;
	NW->prev = other.NW->prev;
	temp = other.NW->next;
	while (temp->next) {
		InsertBack(temp->data);
		temp = temp->next;
	}

}

/**
 * If you have declared any private helper functions in chain_private.h,
 * add your completed implementations below.
**/

