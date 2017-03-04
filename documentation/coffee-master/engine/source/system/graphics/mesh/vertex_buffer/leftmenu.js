function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6377\" class=\"headerLeftMenuInActive\"><a id=\"aID6377\" href=\"#\" OnMouseOver=\"link('_dir','vertex_buffer0',this)\" class=\"leftMenuLinkHeadInActive\">vertex_buffer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID885\" class=\"leftMenuInActive\"><a id=\"aID885\" href=\"#\" OnMouseOver=\"link('_class','VertexBuffer54809',this)\" class=\"leftMenuLinkInActive\">VertexBuffer</a></div>\n");
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
