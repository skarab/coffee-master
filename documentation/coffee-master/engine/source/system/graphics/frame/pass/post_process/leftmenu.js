function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6365\" class=\"headerLeftMenuInActive\"><a id=\"aID6365\" href=\"#\" OnMouseOver=\"link('_dir','post_process0',this)\" class=\"leftMenuLinkHeadInActive\">post_process</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID869\" class=\"leftMenuInActive\"><a id=\"aID869\" href=\"#\" OnMouseOver=\"link('_class','FramePassPostProcess54809',this)\" class=\"leftMenuLinkInActive\">FramePassPostProcess</a></div>\n");
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
