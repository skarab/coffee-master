function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6357\" class=\"headerLeftMenuInActive\"><a id=\"aID6357\" href=\"#\" OnMouseOver=\"link('_dir','buffer0',this)\" class=\"leftMenuLinkHeadInActive\">buffer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID860\" class=\"leftMenuInActive\"><a id=\"aID860\" href=\"#\" OnMouseOver=\"link('_class','FrameBuffer54809',this)\" class=\"leftMenuLinkInActive\">FrameBuffer</a></div>\n");
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
