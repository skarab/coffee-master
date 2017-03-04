function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6449\" class=\"headerLeftMenuInActive\"><a id=\"aID6449\" href=\"#\" OnMouseOver=\"link('_dir','image0',this)\" class=\"leftMenuLinkHeadInActive\">image</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1023\" class=\"leftMenuInActive\"><a id=\"aID1023\" href=\"#\" OnMouseOver=\"link('_class','Image45101',this)\" class=\"leftMenuLinkInActive\">Image</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6244\" class=\"leftMenuInActive\"><a id=\"aID6244\" href=\"#\" OnMouseOver=\"link('_member','IMAGE_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">IMAGE_STYLE</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
